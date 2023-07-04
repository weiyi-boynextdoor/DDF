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

    void PickPhysicalDevice();

    void CreateLogicDevice();

private:
    VkInstance instance_{nullptr};
    VkDebugUtilsMessengerEXT debug_messenger_{nullptr};

    VkPhysicalDevice physical_device_{nullptr};
    VkDevice device_{nullptr};

    VkQueue graphics_queue_{nullptr};

    bool enable_validation_layers_{false};
};
} // namespace DDF