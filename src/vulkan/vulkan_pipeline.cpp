#include "vulkan_pipeline.h"

namespace DDF {
VulkanPipeline::VulkanPipeline(VkDevice device, VkPipeline pipeline, VkPipelineLayout layout) :
    device_(device), pipeline_(pipeline), pipeline_layout_(layout) {
}

VulkanPipeline::~VulkanPipeline() {
    vkDestroyPipeline(device_, pipeline_, nullptr);
    vkDestroyPipelineLayout(device_, pipeline_layout_, nullptr);
}

} // namespace DDF
