#include "Core.h"

namespace gip{
    void Core::load(){
        _window = new OpenGLWindow(1920, 1080, "SDFDDGI");
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
           FATAL("Failed to initialize GLAD");
        }


        _testScene.load();

    }

    void Core::update(){
        if(InputManager::isKeyPressed(KeyCodes::KEY_A)) LOG("A pressed");

        _testScene.update();
        InputManager::clear();
        _window->update();
    }

    void Core::render(){
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        _testScene.render();
        _window->render();
    }

    void Core::unload(){
        _window->unload();
        _testScene.unload();
    }
}