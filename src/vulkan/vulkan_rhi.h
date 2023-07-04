#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>

namespace DDF {
struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool IsComplete() {
        return graphics_family.has_value() && present_family.has_value();
    }
};

class VulkanRHI {
public:
    VulkanRHI();

    ~VulkanRHI() = default;

    void Init(GLFWwindow* window);

    void Destroy();

private:
    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicDevice();

    std::vector<const char*> GetRequiredExtensions() const;

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device);

private:
    GLFWwindow* window_{nullptr};
    VkInstance instance_{nullptr};
    VkDebugUtilsMessengerEXT debug_messenger_{nullptr};
    VkSurfaceKHR surface_{nullptr};

    VkPhysicalDevice physical_device_{nullptr};
    VkDevice device_{nullptr};

    VkQueue graphics_queue_{nullptr};
    VkQueue present_queue_{nullptr};

    bool enable_validation_layers_{false};
};
} // namespace DDF