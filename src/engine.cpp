#include "engine.h"

namespace DDF {
Engine::Engine() {
    rhi_ = std::make_unique<VulkanRHI>();
}

Engine::~Engine() {
    rhi_->destroy();
    rhi_.reset();
}

void Engine::init(GLFWwindow* window) {
    rhi_->init(window);
}
} // namespace DDF
