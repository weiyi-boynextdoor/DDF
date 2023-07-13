#include "renderer.h"

namespace DDF {
Renderer::Renderer(VulkanRHI* rhi) : rhi_(rhi) {
}

void Renderer::init() {
    triangle_pass_ = std::make_unique<TrianglePass>(rhi_);
    triangle_pass_->init();
}

void Renderer::destroy() {
    triangle_pass_->destroy();
    triangle_pass_.reset();
}

void Renderer::render() {
    if (rhi_->beginFrame()) {
        triangle_pass_->draw();
        rhi_->submitRender();
    }
}

void Renderer::recreateFrameBuffer() {
    triangle_pass_->recreateFrameBuffer();
}
} // namespace DDF
