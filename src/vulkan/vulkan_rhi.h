#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>

namespace DDF {
struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool isComplete() {
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

    void init(GLFWwindow* window);

    void destroy();

private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicDevice();
    void createSwapChain();

    std::vector<const char*> getRequiredExtensions() const;

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D VulkanRHI::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

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
    std::vector<VkImage> swap_chain_images_{};
    VkFormat swap_chain_image_format_{};
    VkExtent2D swap_chain_extent_{};

    bool enable_validation_layers_{false};
};
} // namespace DDF