#pragma once

#include <vulkan/vulkan.h>

#include <string>

namespace DDF {
struct PipelineCreateInfo {
    std::string vert_spv;
    std::string frag_spv;
    VkRenderPass render_pass{nullptr};
};

struct RenderPassCreateInfo {};

} // namespace DDF
