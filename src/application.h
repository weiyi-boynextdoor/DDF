#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "vulkan/vulkan_rhi.h"

namespace DDF
{

class Application {
public:
    Application(uint32_t width, uint32_t height);

    ~Application() {}

    void Run();

private:
    uint32_t width_{1080};
    uint32_t height_{720};

    GLFWwindow* window_{nullptr};
    std::unique_ptr<VulkanRHI> rhi_;

    void InitWindow();

    void InitVulkan();

    void MainLoop();

    void CleanUp();

    void CreateInstance();
};

} // namespace DDF
