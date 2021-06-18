#include "OpenGLWindow.h"

namespace gip{

    OpenGLWindow::OpenGLWindow(int width, int height, const char* windowName):_width(width), _height(height), _name(windowName){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        _window = glfwCreateWindow(width, height, windowName, 0, 0);
        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));

        glfwSetFramebufferSizeCallback(_window, OpenGLCallbacks::framebufferSizeCallback);  
        glfwSetWindowSizeCallback(_window, OpenGLCallbacks::windowResizeCallback);
        glfwSetKeyCallback(_window, OpenGLCallbacks::keyCallback);
        glfwSetMouseButtonCallback(_window, OpenGLCallbacks::mouseClickCallback);
        glfwSetCursorPosCallback(_window, OpenGLCallbacks::cursorPositionCallback);
    }


    void OpenGLWindow::update(){
        glfwPollEvents();    
    }
    void OpenGLWindow::render(){
        glfwSwapBuffers(_window);
    }
    void OpenGLWindow::destroy(){
        WARN("Destroying OpenGLWindow");
        glfwTerminate();
    }



    void OpenGLWindow::setSize(int width, int height){
        _width = width;
        _height = height;
        glfwSetWindowSize(_window, _width, _height);
    }

    void OpenGLWindow::setPosition(int x, int y){
        glfwSetWindowPos(_window, x, y);
    }



}