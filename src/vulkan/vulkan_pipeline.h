#pragma once

#include <vulkan/vulkan.h>

#include <string>

namespace DDF {
struct PipelineCreateInfo {
    std::string vert_spv;
    std::string frag_spv;
};

class VulkanPipeline {
public:
    VulkanPipeline();
    ~VulkanPipeline();

private:
    VkPipelineLayout pipeline_layout_;
    VkPipeline pipeline_;
};
} // namespace DDF
