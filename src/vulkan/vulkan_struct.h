#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace DDF {
struct PipelineCreateInfo {
    std::string vert_spv;
    std::string frag_spv;
    VkRenderPass render_pass;
};

struct RenderPassCreateInfo {};

struct RenderPassCommandInfo {
    VkRenderPass render_pass;
    VkPipeline pipeline;
    VkFramebuffer frame_buffer;
};

struct FrameBufferCreateInfo {
    VkImageView* attachments;
    uint32_t attachment_count;
    VkRenderPass render_pass;
    uint32_t width;
    uint32_t height;
};

struct SwapChainDesc {
    VkExtent2D extent;
    VkFormat image_format;
    VkViewport viewport;
    VkRect2D scissor;
    std::vector<VkImageView> image_views;
};

} // namespace DDF
