set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
	Engine SHARED 
	src/Engine/Test.cpp
	src/Engine/Test.h
	)


add_custom_command(TARGET Engine PRE_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
    "${VULKAN_ROOT}/Lib/vulkan-1.lib"      
    "${EXECUTABLE_OUTPUT_PATH}")                 

add_custom_command(TARGET Engine PRE_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
    "${GLFW_ABS_LIB}/glfw3dll.lib"      
    "${EXECUTABLE_OUTPUT_PATH}")  

add_custom_command(TARGET Engine PRE_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
    "${GLFW_ABS_LIB}/glfw3.dll"      
    "${EXECUTABLE_OUTPUT_PATH}")  


target_compile_definitions(Engine PUBLIC ENGINE_NAME=Engine)

target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(Engine PUBLIC "${ENTT_ABS_ROOT}")
target_include_directories(Engine PUBLIC "${GLFW_ABS_INCLUDE}")
target_include_directories(Engine PUBLIC "${EXTERN_DIR}/glm")
target_include_directories(Engine PUBLIC "${EXTERN_DIR}/stbimage")
target_include_directories(Engine PUBLIC "${VULKAN_INCLUDE}")
target_include_directories(Engine PUBLIC "${FMT_ROOT}/include")
target_include_directories(Engine PUBLIC "${GLAD_INC}")

target_link_directories(Engine PUBLIC "${GLFW_ABS_LIB}")
target_link_directories(Engine PUBLIC "${VULKAN_LIB}")
target_link_directories(Engine PUBLIC "${FMT_ROOT}/")
target_link_libraries(Engine glfw3dll)
target_link_libraries(Engine vulkan-1)
target_link_libraries(Engine pthread)
target_link_libraries(Engine fmt::fmt-header-only)
target_link_libraries(Engine glad)

find_package(OpenGL REQUIRED)
target_link_libraries(Engine OpenGL::GL)


