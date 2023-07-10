#include "triangle_pass.h"
#include "core/file_utils.h"

namespace DDF {
void TrianglePass::init() {
    auto vert_spv = DDF::readFile("shaders/generated/triangle.vert.spv");
    auto frag_spv = DDF::readFile("shaders/generated/triangle.frag.spv");
    render_pass_ = rhi_->createRenderPass({});
    DDF::PipelineCreateInfo pipeline_info{std::move(vert_spv), std::move(frag_spv), render_pass_};
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

void TrianglePass::draw() {
    RenderPassCreateInfo create_info{.render_pass = render_pass_,
                                     .pipeline = pipeline_->getPipeline(),
                                     .frame_buffer = frame_buffers_[rhi_->getCurFrameBufferIndex()]};
    rhi_->recordCommandBuffer(rhi_->getCommandBuffer(), create_info);
}

void TrianglePass::destroy() {
    auto device = rhi_->getDevice();

    for (auto frame_buffer : frame_buffers_) {
        vkDestroyFramebuffer(device, frame_buffer, nullptr);
    }

    pipeline_.reset();
    vkDestroyRenderPass(device, render_pass_, nullptr);
}
} // namespace DDF
