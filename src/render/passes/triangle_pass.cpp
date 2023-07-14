#include <core/file_utils.h>
#include <render/passes/triangle_pass.h>

#include <stdexcept>

namespace DDF {
TrianglePass::TrianglePass(VulkanRHI* rhi) : RenderPass(rhi) {
    vertices_ = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                 {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                 {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                 {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};
    indices_ = {0, 2, 1, 2, 0, 3};
}

void TrianglePass::init() {
    createVertexBuffer();
    createIndexBuffer();

    auto vert_spv = DDF::readFile("shaders/generated/triangle.vert.spv");
    auto frag_spv = DDF::readFile("shaders/generated/triangle.frag.spv");
    render_pass_ = rhi_->createRenderPass({});

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    DDF::PipelineCreateInfo pipeline_info{
        std::move(vert_spv), std::move(frag_spv), render_pass_, &bindingDescription, attributeDescriptions.data(), 2};
    pipeline_ = std::move(rhi_->createGraphicsPipeline(pipeline_info));
    auto swapchain_desc = rhi_->getSwapChainDesc();
    frame_buffers_.resize(swapchain_desc.image_views.size());
    for (size_t i = 0; i < swapchain_desc.image_views.size(); ++i) {
        DDF::FrameBufferCreateInfo create_info{};
        create_info.attachments = &swapchain_desc.image_views[i];
        create_info.attachment_count = 1;
        create_info.width = swapchain_desc.extent.width;
        create_info.height = swapchain_desc.extent.height;
        create_info.render_pass = render_pass_;
        frame_buffers_[i] = rhi_->createFrameBuffer(create_info);
    }
}

void TrianglePass::createVertexBuffer() {
    auto device = rhi_->getDevice();

    VkDeviceSize bufferSize = sizeof(vertices_[0]) * vertices_.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    rhi_->createBuffer(bufferSize,
                       VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                       stagingBuffer,
                       stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices_.data(), (size_t)bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    rhi_->createBuffer(bufferSize,
                       VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                       vertex_buffer_,
                       vertex_buffer_memory_);

    rhi_->copyBuffer(stagingBuffer, vertex_buffer_, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void TrianglePass::createIndexBuffer() {
    auto device = rhi_->getDevice();

    VkDeviceSize bufferSize = sizeof(indices_[0]) * indices_.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    rhi_->createBuffer(bufferSize,
                       VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                       stagingBuffer,
                       stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices_.data(), (size_t)bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    rhi_->createBuffer(bufferSize,
                       VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                       index_buffer_,
                       index_buffer_memory_);

    rhi_->copyBuffer(stagingBuffer, index_buffer_, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void TrianglePass::draw() {
    RenderPassCommandInfo create_info{.render_pass = render_pass_,
                                      .pipeline = pipeline_->getPipeline(),
                                      .frame_buffer = frame_buffers_[rhi_->getCurFrameBufferIndex()],
                                      .vertex_buffer = vertex_buffer_,
                                      .index_buffer = index_buffer_,
                                      .index_size = (uint32_t)indices_.size()};
    rhi_->recordCommandBuffer(rhi_->getCommandBuffer(), create_info);
}

void TrianglePass::destroy() {
    auto device = rhi_->getDevice();

    vkDestroyBuffer(device, index_buffer_, nullptr);
    vkFreeMemory(device, index_buffer_memory_, nullptr);

    vkDestroyBuffer(device, vertex_buffer_, nullptr);
    vkFreeMemory(device, vertex_buffer_memory_, nullptr);

    for (auto frame_buffer : frame_buffers_) {
        vkDestroyFramebuffer(device, frame_buffer, nullptr);
    }

    pipeline_.reset();
    vkDestroyRenderPass(device, render_pass_, nullptr);
}

void TrianglePass::recreateFrameBuffer() {
    auto device = rhi_->getDevice();

    for (auto frame_buffer : frame_buffers_) {
        vkDestroyFramebuffer(device, frame_buffer, nullptr);
    }

    auto swapchain_desc = rhi_->getSwapChainDesc();
    for (size_t i = 0; i < swapchain_desc.image_views.size(); ++i) {
        DDF::FrameBufferCreateInfo create_info{};
        create_info.attachments = &swapchain_desc.image_views[i];
        create_info.attachment_count = 1;
        create_info.width = swapchain_desc.extent.width;
        create_info.height = swapchain_desc.extent.height;
        create_info.render_pass = render_pass_;
        frame_buffers_[i] = rhi_->createFrameBuffer(create_info);
    }
}
} // namespace DDF
