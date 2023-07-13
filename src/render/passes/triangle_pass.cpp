#include <core/file_utils.h>
#include <render/passes/triangle_pass.h>

#include <stdexcept>

namespace DDF {
TrianglePass::TrianglePass(VulkanRHI* rhi) : RenderPass(rhi) {
    vertices_ = {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}, {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}};
}

void TrianglePass::init() {
    createVertexBuffer();

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

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(vertices_[0]) * vertices_.size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &vertex_buffer_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, vertex_buffer_, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(
        memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &vertex_buffer_memory_) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(device, vertex_buffer_, vertex_buffer_memory_, 0);

    void* data;
    vkMapMemory(device, vertex_buffer_memory_, 0, bufferInfo.size, 0, &data);
    memcpy(data, vertices_.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(device, vertex_buffer_memory_);
}

uint32_t TrianglePass::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    auto physicalDevice = rhi_->getPhysicalDevice();

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void TrianglePass::draw() {
    RenderPassCommandInfo create_info{.render_pass = render_pass_,
                                      .pipeline = pipeline_->getPipeline(),
                                      .frame_buffer = frame_buffers_[rhi_->getCurFrameBufferIndex()],
                                      .vertex_buffer = vertex_buffer_};
    rhi_->recordCommandBuffer(rhi_->getCommandBuffer(), create_info);
}

void TrianglePass::destroy() {
    auto device = rhi_->getDevice();

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
