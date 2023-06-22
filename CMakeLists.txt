cmake_minimum_required(VERSION 3.8)

project(VulkanEngine)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(DDF src/main.cpp)