#pragma once

#include <memory>

#include "systems/render_system.h"
#include "vulkan/vulkan_rhi.h"

namespace DDF {
struct Context {
    GLFWwindow* window{nullptr};
    std::unique_ptr<VulkanRHI> rhi;
    std::unique_ptr<RenderSystem> render_system;
};
} // namespace DDF
