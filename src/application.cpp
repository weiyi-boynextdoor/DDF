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

void Application::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(width_, height_, "Vulkan", nullptr, nullptr);
    context_.window = window_;
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        engine_->update();
    }
}

void Application::cleanUp() {
    engine_.reset();

    glfwDestroyWindow(window_);

    glfwTerminate();
}

} // namespace DDF
