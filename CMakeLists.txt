cmake_minimum_required(VERSION 3.8)
project(SDFDDGI LANGUAGES CXX C)
set (CMAKE_CXX_STANDARD 17)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDFDDGI)

# GLOB_RECURSE is okay for now, just remember to rerun cmake when you add a new file
file(GLOB_RECURSE SRC_FILES "Engine/*.cpp" "Engine/*.h")

find_package(OpenGL REQUIRED)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_INSTALL "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
add_subdirectory(dep/glfw)
add_subdirectory(dep/fmt)
add_subdirectory(dep/glm)
add_subdirectory(dep/glad)
add_subdirectory(dep/assimp)

add_executable(SDFDDGI ${SRC_FILES})
target_link_libraries(SDFDDGI PRIVATE ${OPENGL_gl_LIBRARY}) # Do we really need to load it? It seems that glad loads the library dynamically.
target_link_libraries(SDFDDGI PRIVATE glfw)
target_link_libraries(SDFDDGI PRIVATE fmt)
target_link_libraries(SDFDDGI PRIVATE glm)
target_link_libraries(SDFDDGI PRIVATE glad)
target_link_libraries(SDFDDGI PRIVATE assimp)
# target_compile_definitions(SDFDDGI PUBLIC _DEBUG_MODE_=1) This should be a command line argument

target_include_directories(SDFDDGI PRIVATE "dep/glfw/include")
target_include_directories(SDFDDGI PRIVATE "dep/fmt/include")
target_include_directories(SDFDDGI PRIVATE "dep/stb_image")
target_include_directories(SDFDDGI PRIVATE ".")