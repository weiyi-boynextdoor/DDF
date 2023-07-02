#include "application.h"

namespace DDF
{
Application::Application(uint32_t width, uint32_t height) : width_(width), height_(height) {}

void Application::Run() {
    InitWindow();
    InitVulkan();
    MainLoop();
    CleanUp();
}

void Application::InitWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(width_, height_, "Vulkan", nullptr, nullptr);
}

void Application::InitVulkan() {
    rhi_ = std::make_unique<VulkanRHI>();
    rhi_->Init();
}

void Application::MainLoop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
    }
}

void Application::CleanUp() {
    rhi_->Destroy();
    rhi_.reset();

    glfwDestroyWindow(window_);

    glfwTerminate();
}

} // namespace DDF
