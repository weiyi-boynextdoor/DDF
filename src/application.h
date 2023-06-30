#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace DDF
{

class Application
{
public:
    Application(uint32_t width, uint32_t height);

    ~Application() {}

    void Run()
    {
        InitWindow();
        InitVulkan();
        MainLoop();
        CleanUp();
    }

private:
    uint32_t width_  = 1080;
    uint32_t height_ = 720;

    GLFWwindow* window_   = nullptr;
    VkInstance  instance_ = nullptr;

    void InitWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window_ = glfwCreateWindow(width_, height_, "Vulkan", nullptr, nullptr);
    }

    void InitVulkan() { CreateInstance(); }

    void MainLoop()
    {
        while (!glfwWindowShouldClose(window_))
        {
            glfwPollEvents();
        }
    }

    void CleanUp()
    {
        vkDestroyInstance(instance_, nullptr);

        glfwDestroyWindow(window_);

        glfwTerminate();
    }

    void CreateInstance()
    {
        VkApplicationInfo appInfo {};
        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName   = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName        = "No Engine";
        appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion         = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo {};
        createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t     glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount   = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance_) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }
};

} // namespace DDF
