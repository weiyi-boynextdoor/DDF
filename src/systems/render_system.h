#pragma once

#include "vulkan/vulkan_rhi.h"

namespace DDF {
struct Context;

class RenderSystem {
public:
    RenderSystem(VulkanRHI& rhi);

    ~RenderSystem() = default;

private:
    VulkanRHI& rhi_;
};
} // namespace DDF
