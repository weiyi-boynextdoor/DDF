cmake_minimum_required(VERSION 3.12)

project(DDF)

set(TARGET_NAME DDF)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET_NAME} Vulkan::Vulkan glfw)