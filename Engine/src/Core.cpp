#include "Core.h"

namespace gip{
    void Core::load(){
        _window = new OpenGLWindow(1920, 1080, "SDFDDGI");
    }

    void Core::update(){
        if(InputManager::isKeyPressed(KeyCodes::KEY_A)) LOG("A pressed");

        
        InputManager::clear();
        _window->update();
    }

    void Core::render(){
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        _window->render();
    }

    void Core::unload(){
        _window->unload();
    }
}