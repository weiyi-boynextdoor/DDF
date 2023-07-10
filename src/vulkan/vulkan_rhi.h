#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "vulkan_pipeline.h"
#include "vulkan_struct.h"

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

    VkDevice getDevice() const {
        return device_;
    }

    uint32_t getSwapChainSize() const {
        return (uint32_t)swapchain_images_.size();
    }

    SwapChainDesc getSwapChainDesc() const;

    std::unique_ptr<VulkanPipeline> createGraphicsPipeline(const PipelineCreateInfo& create_info);

    VkRenderPass createRenderPass(const RenderPassCreateInfo& create_info);

    VkFramebuffer createFrameBuffer(const FrameBufferCreateInfo& create_info);

    void recordCommandBuffer(VkCommandBuffer commandBuffer, const RenderPassCreateInfo& create_info);

    void beginFrame();

    void submitRender();

    uint32_t getCurFrameBufferIndex() const {
        return swapchain_cur_index_;
    }

    VkCommandBuffer getCommandBuffer() const {
        return command_buffer_;
    }

private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicDevice();
    void createSwapChain();
    void createImageViews();
    void createCommandPool();
    void createCommandBuffer();
    void createSyncObjects();

    std::vector<const char*> getRequiredExtensions() const;

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

private:
    GLFWwindow* window_{nullptr};
    VkInstance instance_{nullptr};
    VkDebugUtilsMessengerEXT debug_messenger_{nullptr};
    VkSurfaceKHR surface_{nullptr};

    VkPhysicalDevice physical_device_{nullptr};
    VkDevice device_{nullptr};

    VkQueue graphics_queue_{nullptr};
    VkQueue present_queue_{nullptr};

    VkSwapchainKHR swapchain_{nullptr};
    std::vector<VkImage> swapchain_images_;
    VkFormat swapchain_image_format_{};
    VkExtent2D swapchain_extent_{};
    std::vector<VkImageView> swapchain_imageviews_;
    uint32_t swapchain_cur_index_{0};

    VkCommandPool command_pool_{nullptr};
    VkCommandBuffer command_buffer_{nullptr};

    VkSemaphore image_available_semaphore_{nullptr};
    VkSemaphore render_finished_semaphore_{nullptr};
    VkFence in_flight_fence_{nullptr};

    bool enable_validation_layers_{false};
};
} // namespace DDF
