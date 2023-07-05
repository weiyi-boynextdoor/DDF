#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "engine.h"

namespace DDF
{

class Application {
public:
    using SetupCallback = std::function<void(Engine*)>;
    using CleanupCallback = std::function<void(Engine*)>;

    Application(uint32_t width, uint32_t height);

    ~Application() {}

    void run(SetupCallback setup = nullptr, CleanupCallback cleanup = nullptr);

private:
    uint32_t width_{1080};
    uint32_t height_{720};

    GLFWwindow* window_{nullptr};
    std::unique_ptr<Engine> engine_;

    void initWindow();

    void mainLoop();

    void cleanUp();

    void createInstance();
};

} // namespace DDF
