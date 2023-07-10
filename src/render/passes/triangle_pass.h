#pragma once

#include <memory>
#include <vector>

#include <render/render_pass.h>

namespace DDF {
class TrianglePass : public RenderPass {
public:
    TrianglePass(VulkanRHI* rhi) : RenderPass(rhi) {
    }

    void init() override;

    void draw() override;

    void destroy() override;

protected:
    std::unique_ptr<DDF::VulkanPipeline> pipeline_;
    VkRenderPass render_pass_{};
    std::vector<VkFramebuffer> frame_buffers_;
};
} // namespace DDF
