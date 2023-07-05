cmake_minimum_required(VERSION 3.12)

project(DDF)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(shader)
add_subdirectory(src)
