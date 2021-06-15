cmake_minimum_required(VERSION 3.8)
project(SDFDDGI LANGUAGES CXX C)
set (CMAKE_CXX_STANDARD 17)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDFDDGI)

# GLOB_RECURSE is okay for now, just remember to rerun cmake when you add a new file
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h")

find_package(OpenGL REQUIRED)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_INSTALL "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
add_subdirectory(dep/glfw)

add_executable(SDFDDGI ${SRC_FILES})
target_link_libraries(SDFDDGI PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(SDFDDGI PRIVATE glfw)

target_include_directories(SDFDDGI PRIVATE "dep/glfw/include")