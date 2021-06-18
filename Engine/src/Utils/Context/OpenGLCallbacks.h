#pragma once
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Utils/Context/OpenGLWindow.h>
#include <Engine/src/Utils/Input/GLFWInputKeyStore.h>
#include <Engine/src/Utils/Input/InputManager.h>
#include <GLFW/glfw3.h>

namespace gip{
    class OpenGLCallbacks{
        public:
            OpenGLCallbacks() = delete;
            static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
            static void windowResizeCallback(GLFWwindow *window, int width, int height);
	        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
            static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
            static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    };
}