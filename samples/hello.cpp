
#include <iostream>

#include "application.h"
#include "core/file_utils.h"

int main() {
    DDF::Application app(1080, 720);

    std::unique_ptr<DDF::VulkanPipeline> pipeline;
    VkRenderPass render_pass{};
    std::vector<VkFramebuffer> frame_buffers;

    auto setup = [&](DDF::Engine* engine) {
        auto vert_spv = DDF::readFile("shaders/generated/triangle.vert.spv");
        auto frag_spv = DDF::readFile("shaders/generated/triangle.frag.spv");

        auto* rhi = engine->getRHI();
        render_pass = rhi->createRenderPass({});
        DDF::PipelineCreateInfo pipeline_info{std::move(vert_spv), std::move(frag_spv), render_pass};
        pipeline = std::move(rhi->createGraphicsPipeline(pipeline_info));

        auto swapchain_desc = rhi->getSwapChainDesc();
        frame_buffers.resize(swapchain_desc.image_views.size());
        for (size_t i = 0; i < swapchain_desc.image_views.size(); ++i) {
            DDF::FrameBufferCreateInfo create_info{};
            create_info.attachments = &swapchain_desc.image_views[i];
            create_info.attachment_count = 1;
            create_info.width = swapchain_desc.extent.width;
            create_info.height = swapchain_desc.extent.height;
            create_info.render_pass = render_pass;
            frame_buffers[i] = rhi->createFrameBuffer(create_info);
        }
    };

    auto cleanup = [&](DDF::Engine* engine) {
        auto* rhi = engine->getRHI();
        auto device = rhi->getDevice();

        for (auto frame_buffer : frame_buffers) {
            vkDestroyFramebuffer(device, frame_buffer, nullptr);
        }

        pipeline.reset();
        vkDestroyRenderPass(device, render_pass, nullptr);
    };

    app.run(setup, cleanup);
    return 0;
}