
#include <iostream>

#include "application.h"
#include "core/file_utils.h"

int main() {
    DDF::Application app(1080, 720);

    auto setup = [&app](DDF::Engine* engine) {
        auto vert_spv = DDF::readFile("shaders/generated/triangle.vert.spv");
        auto frag_spv = DDF::readFile("shaders/generated/triangle.frag.spv");

        auto* rhi = engine->getRHI();
        DDF::PipelineCreateInfo pipeline_info{std::move(vert_spv), std::move(frag_spv)};
        rhi->createGraphicsPipeline(pipeline_info);
    };

    auto cleanup = [&app](DDF::Engine* engine) {

    };

    app.run(setup, cleanup);
    return 0;
}