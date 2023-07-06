#pragma once

#include <vulkan/vulkan.h>

#include <string>

namespace DDF {
class VulkanPipeline {
public:
    VulkanPipeline() = default;
    VulkanPipeline(VkDevice device, VkPipeline pipeline, VkPipelineLayout layout);

    VulkanPipeline(const VulkanPipeline&) = delete;
    VulkanPipeline(VulkanPipeline&&) = delete;

    ~VulkanPipeline();

private:
    VkDevice device_{nullptr};
    VkPipeline pipeline_{nullptr};
    VkPipelineLayout pipeline_layout_{nullptr};
};
} // namespace DDF
