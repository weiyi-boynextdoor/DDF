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

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
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
    void CreateSwapChain();

    std::vector<const char*> GetRequiredExtensions() const;

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device);

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D VulkanRHI::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

private:
    GLFWwindow* window_{nullptr};
    VkInstance instance_{nullptr};
    VkDebugUtilsMessengerEXT debug_messenger_{nullptr};
    VkSurfaceKHR surface_{nullptr};

    VkPhysicalDevice physical_device_{nullptr};
    VkDevice device_{nullptr};

    VkQueue graphics_queue_{nullptr};
    VkQueue present_queue_{nullptr};

    VkSwapchainKHR swap_chain_{nullptr};
    std::vector<VkImage> swap_chain_images_;
    VkFormat swap_chain_image_format_;
    VkExtent2D swap_chain_extent_;

    bool enable_validation_layers_{false};
};
} // namespace DDF