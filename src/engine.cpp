#include "engine.h"
#include "context.h"

namespace DDF {
Engine::Engine(Context& context) : context_(context) {
}

Engine::~Engine() {
}

void Engine::init() {
    context_.rhi = std::make_unique<VulkanRHI>();
    context_.rhi->init(context_.window);
    context_.renderer = std::make_unique<Renderer>(context_.rhi.get());
    context_.renderer->init();

    context_.rhi->setRecreateSwapChainCallback([this]() { context_.renderer->recreateFrameBuffer(); });
}

void Engine::destroy() {
    context_.rhi->waitIdle();
    context_.renderer->destroy();
    context_.renderer.reset();
    context_.rhi->destroy();
    context_.rhi.reset();
}

void Engine::update() {
    context_.renderer->render();
}
} // namespace DDF
