#include "engine.h"
#include "context.h"

namespace DDF {
Engine::Engine(Context& context) : context_(context) {
}

Engine::~Engine() {
}

void Engine::initSystems() {
    context_.rhi = std::make_unique<VulkanRHI>();
    context_.rhi->init(context_.window);
    context_.render_system = std::make_unique<RenderSystem>(*context_.rhi);
}

void Engine::destroySystems() {
    context_.render_system.reset();
    context_.rhi->destroy();
    context_.rhi.reset();
}
} // namespace DDF
