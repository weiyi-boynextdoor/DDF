#pragma once

#include <memory>
#include <vector>

#include <render/render_pass.h>

namespace DDF {
class TrianglePass : public RenderPass {
public:
    TrianglePass(VulkanRHI* rhi);

    void init() override;

    void draw() override;

    void destroy() override;

    void recreateFrameBuffer();

private:
    void createVertexBuffer();

    void createIndexBuffer();

private:
    std::unique_ptr<DDF::VulkanPipeline> pipeline_;
    VkRenderPass render_pass_{};
    std::vector<VkFramebuffer> frame_buffers_;

    VkBuffer vertex_buffer_;
    VkDeviceMemory vertex_buffer_memory_;
    std::vector<Vertex> vertices_;

    VkBuffer index_buffer_;
    VkDeviceMemory index_buffer_memory_;
    std::vector<uint16_t> indices_;
};
} // namespace DDF
