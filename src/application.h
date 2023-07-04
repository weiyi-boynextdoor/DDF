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

    void run();

private:
    uint32_t width_{1080};
    uint32_t height_{720};

    GLFWwindow* window_{nullptr};
    std::unique_ptr<VulkanRHI> rhi_;

    void initWindow();

    void initVulkan();

    void mainLoop();

    void cleanUp();

    void createInstance();
};

} // namespace DDF
