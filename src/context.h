#pragma once

#include <memory>

#include <render/renderer.h>

namespace DDF {
struct Context {
    GLFWwindow* window{nullptr};
    std::unique_ptr<VulkanRHI> rhi;
    std::unique_ptr<Renderer> renderer;
};
} // namespace DDF
