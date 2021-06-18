#pragma once
#include <GLFW/glfw3.h>
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Utils/Context/OpenGLWindow.h>
#include <Engine/src/Utils/Context/OpenGLCallbacks.h>
namespace gip{

    class OpenGLWindow{
        private:
            GLFWwindow* _window;
            int _width, _height;
            const char* _name;
        public:
            OpenGLWindow(int width, int height, const char* windowName);
            void update();
            void render();
            void unload();
            void setSize(int width, int height);
            void setPosition(int x, int y);

        
            inline bool shouldClose(){return glfwWindowShouldClose(_window);}
    };

}