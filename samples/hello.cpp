
#include <iostream>

#include "application.h"
#include "core/file_utils.h"

int main() {
    DDF::Application app(1080, 720);

    std::unique_ptr<DDF::VulkanPipeline> pipeline;
    VkRenderPass render_pass{};

    auto setup = [&app, &pipeline, &render_pass](DDF::Engine* engine) {
        auto vert_spv = DDF::readFile("shaders/generated/triangle.vert.spv");
        auto frag_spv = DDF::readFile("shaders/generated/triangle.frag.spv");

        auto* rhi = engine->getRHI();
        render_pass = rhi->createRenderPass({});
        DDF::PipelineCreateInfo pipeline_info{std::move(vert_spv), std::move(frag_spv), render_pass};
        pipeline = std::move(rhi->createGraphicsPipeline(pipeline_info));
    };

    auto cleanup = [&app, &pipeline, &render_pass](DDF::Engine* engine) {
        pipeline.reset();
        auto device = engine->getRHI()->getDevice();
        vkDestroyRenderPass(device, render_pass, nullptr);
    };

    app.run(setup, cleanup);
    return 0;
}