#include "application.h"

namespace DDF
{
Application::Application(uint32_t width, uint32_t height) : width_(width), height_(height) {}

void Application::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanUp();
}

void Application::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(width_, height_, "Vulkan", nullptr, nullptr);
}

void Application::initVulkan() {
    rhi_ = std::make_unique<VulkanRHI>();
    rhi_->init(window_);
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
    }
}

void Application::cleanUp() {
    rhi_->destroy();
    rhi_.reset();

    glfwDestroyWindow(window_);

    glfwTerminate();
}

} // namespace DDF
