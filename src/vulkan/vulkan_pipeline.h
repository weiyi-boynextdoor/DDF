#pragma once

#include <vulkan/vulkan.h>

#include <string>

#include "vulkan_struct.h"

namespace DDF {
class VulkanPipeline {
public:
    VulkanPipeline(VkDevice device, const PipelineCreateInfo& create_info);

    VulkanPipeline(const VulkanPipeline&) = delete;
    VulkanPipeline(VulkanPipeline&&) = delete;

    ~VulkanPipeline();

private:
    VkDevice device_{nullptr};
    VkPipeline pipeline_{nullptr};
    VkPipelineLayout pipeline_layout_{nullptr};
};
} // namespace DDF
