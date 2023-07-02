#pragma once

#include <vulkan/vulkan.h>

namespace DDF {
class VulkanRHI {
public:
    VulkanRHI() = default;

    ~VulkanRHI() = default;

    void Init();

    void Destroy();

private:
    void CreateInstance();

private:
    VkInstance instance_{nullptr};
};
} // namespace DDF