#pragma once

#include "vulkan/vulkan_rhi.h"

#include <memory>

namespace DDF {
class Engine {
public:
    Engine();

    ~Engine();

    void init(GLFWwindow* window);

    void update() {
    }

    VulkanRHI* getRHI() const {
        return rhi_.get();
    }

private:
    std::unique_ptr<VulkanRHI> rhi_;
};
} // namespace DDF