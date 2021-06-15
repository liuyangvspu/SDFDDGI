cmake_minimum_required(VERSION 3.13.4)
project (EngineMain LANGUAGES CXX VERSION 1.0.0)

set(VULKAN_ROOT "$ENV{VULKAN_SDK}") #make sure your VULKAN_SDK environment variable is set
set(VULKAN_LIB "${VULKAN_ROOT}/Lib/")
set(VULKAN_INCLUDE "${VULKAN_ROOT}/Include")


set(GLFW_ROOT extern/glfw-3.3.3.64)
set(GLFW_ABS_ROOT "${CMAKE_SOURCE_DIR}/${GLFW_ROOT}")
set(GLFW_ABS_LIB "${GLFW_ABS_ROOT}/lib")
set(GLFW_ABS_INCLUDE "${GLFW_ABS_ROOT}/include")

set(ENTT_ROOT extern/entt)
set(ENTT_ABS_ROOT "${CMAKE_SOURCE_DIR}/${ENTT_ROOT}")

set(FMT_ROOT extern/fmt)

set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")

set(GLAD_ROOT "${EXTERN_DIR}/glad")
set(GLAD_INC "${EXTERN_DIR}/glad/include")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

message("${GLFW_ABS_INCLUDE}")

add_subdirectory(Engine) #this needs to be first
add_subdirectory(EngineDriver)
add_subdirectory(extern/fmt EXCLUDE_FROM_ALL)
add_subdirectory(extern/glad)