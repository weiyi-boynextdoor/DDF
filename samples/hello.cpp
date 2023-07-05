
#include <iostream>

#include "application.h"
#include "core/file_utils.h"

int main() {
    DDF::Application app(1080, 720);

    auto setup = [&app](DDF::Engine* engine) {
        auto vert_spv = DDF::readFile("shaders/generated/triangle.vert.spv");
        auto frag_spv = DDF::readFile("shaders/generated/triangle.frag.spv");

        auto* rhi = engine->getRHI();
        auto vert_module = rhi->createShaderModule(vert_spv);
        auto frag_module = rhi->createShaderModule(frag_spv);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vert_module;
        vertShaderStageInfo.pName = "triangle";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = frag_module;
        fragShaderStageInfo.pName = "triangle";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        rhi->destroyShaderModule(vert_module);
        rhi->destroyShaderModule(frag_module);
    };

    auto cleanup = [&app](DDF::Engine* engine) {

    };

    app.run(setup, cleanup);
    return 0;
}