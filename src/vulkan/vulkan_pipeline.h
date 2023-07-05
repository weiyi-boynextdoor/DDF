#pragma once

#include <vulkan/vulkan.h>

#include <string>

namespace DDF {
class VulkanPipeline {
public:
    VulkanPipeline();
    ~VulkanPipeline();

private:
    VkPipelineLayout pipeline_layout_;
    VkPipeline pipeline_;
};
} // namespace DDF
