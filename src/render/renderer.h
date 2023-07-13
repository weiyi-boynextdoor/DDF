#pragma once

#include <memory>

#include <render/passes/triangle_pass.h>
#include <vulkan/vulkan_rhi.h>

namespace DDF {
struct Context;

class Renderer {
public:
    Renderer(VulkanRHI* rhi);

    ~Renderer() = default;

    void init();

    void destroy();

    void render();

    void recreateFrameBuffer();

private:
    VulkanRHI* rhi_;

    std::unique_ptr<TrianglePass> triangle_pass_;
};
} // namespace DDF
