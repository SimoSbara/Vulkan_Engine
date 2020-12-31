cmake_minimum_required(VERSION 3.17)
project(ProvaVulkan)

set(CMAKE_CXX_STANDARD 14)

add_executable(vulkan main.cpp)

include_directories("Vulkan/MoltenVK/include")
include_directories("/usr/local/include")

find_library(
        LIB_VULKAN
        libvulkan.1.2.162.dylib
        PATHS
        Vulkan/MacOS/lib/)

find_library(
        LIB_VULKAN_2
        libvulkan.1.dylib
        PATHS
        Vulkan/MacOS/lib/)

find_library(
        LIB_GLFW
        libglfw.3.3.dylib
        PATHS
        /usr/local/lib/)

target_link_libraries(vulkan ${LIB_VULKAN})
target_link_libraries(vulkan ${LIB_VULKAN_2})
target_link_libraries(vulkan ${LIB_GLFW})


