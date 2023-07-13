#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <vulkan/vulkan_pipeline.h>
#include <vulkan/vulkan_struct.h>

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

    VkPhysicalDevice getPhysicalDevice() const {
        return physical_device_;
    }

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

    void recordCommandBuffer(VkCommandBuffer commandBuffer, const RenderPassCommandInfo& create_info);

    bool beginFrame();

    void submitRender();

    void recreateSwapChain();

    uint32_t getCurFrameBufferIndex() const {
        return swapchain_cur_index_;
    }

    VkCommandBuffer getCommandBuffer() const {
        return command_buffers_[current_frame_];
    }

    void waitIdle() {
        vkDeviceWaitIdle(device_);
    }

    void setRecreateSwapChainCallback(std::function<void()> cb) {
        recreate_swapchain_callback_ = cb;
    }

    void setFrameBufferResized() {
        frame_buffer_resized_ = true;
    }

    static const int k_max_frames_in_flight = 3;

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

    void cleanupSwapChain();

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
    std::vector<VkCommandBuffer> command_buffers_;

    std::vector<VkSemaphore> image_available_semaphores_;
    std::vector<VkSemaphore> render_finished_semaphores_;
    std::vector<VkFence> in_flight_fences_;
    uint32_t current_frame_{0};

    bool frame_buffer_resized_{false};

    std::function<void()> recreate_swapchain_callback_;

    bool enable_validation_layers_{false};
};
} // namespace DDF
