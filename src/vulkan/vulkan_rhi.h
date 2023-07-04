#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace DDF {
class VulkanRHI {
public:
    VulkanRHI();

    ~VulkanRHI() = default;

    void Init();

    void Destroy();

private:
    void CreateInstance();

    std::vector<const char*> GetRequiredExtensions() const;

    void SetupDebugMessenger();

private:
    VkInstance instance_{nullptr};

    VkDebugUtilsMessengerEXT debug_messenger_{nullptr};

    bool enable_validation_layers_{false};
};
} // namespace DDF