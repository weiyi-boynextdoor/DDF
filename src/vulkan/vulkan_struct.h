#pragma once

#include <vulkan/vulkan.h>

#include <array>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace DDF {
struct PipelineCreateInfo {
    std::string vert_spv;
    std::string frag_spv;
    VkRenderPass render_pass;
    VkVertexInputBindingDescription* vertex_binding_desc;
    VkVertexInputAttributeDescription* attr_descs;
    uint32_t attr_num;
};

struct RenderPassCreateInfo {};

struct RenderPassCommandInfo {
    VkRenderPass render_pass;
    VkPipeline pipeline;
    VkFramebuffer frame_buffer;
    VkBuffer vertex_buffer;
    VkBuffer index_buffer;
    uint32_t index_size;
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

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

} // namespace DDF
