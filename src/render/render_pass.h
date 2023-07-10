#pragma once

#include <vulkan/vulkan_rhi.h>

namespace DDF {
class RenderPass {
public:
    RenderPass(VulkanRHI* rhi) : rhi_(rhi) {
    }

    virtual ~RenderPass() = default;

    virtual void init() {
    }

    virtual void draw() {
    }

    virtual void destroy() {
    }

protected:
    VulkanRHI* rhi_{nullptr};
};
} // namespace DDF
