#include "application.h"

namespace DDF
{
Application::Application(uint32_t width, uint32_t height) : width_(width), height_(height) {
}

void Application::run(SetupCallback setup, CleanupCallback cleanup) {
    initWindow();
    engine_ = std::make_unique<Engine>(context_);
    engine_->init();

    if (setup) {
        setup(context_);
    }

    mainLoop();

    if (cleanup) {
        cleanup(context_);
    }
    cleanUp();
}

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->onResize();
}

void Application::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window_ = glfwCreateWindow(width_, height_, "Vulkan", nullptr, nullptr);
    context_.window = window_;

    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebufferResizeCallback);
}

void Application::onResize() {
    context_.rhi->setFrameBufferResized();
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        engine_->update();
    }
}

void Application::cleanUp() {
    engine_->destroy();
    engine_.reset();

    glfwDestroyWindow(window_);

    glfwTerminate();
}

} // namespace DDF
