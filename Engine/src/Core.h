#pragma once
#include <dep/glad/include/glad/glad.h>
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Utils/Input/InputManager.h>
#include <Engine/src/Utils/Context/OpenGLWindow.h>

#include "DebugScene.h"
namespace gip{

    class Core{
        private:
            OpenGLWindow* _window;
            DebugScene _testScene;

        public:
            void load();
            void update();
            void render();
            void unload();
            inline bool shouldClose(){return _window->shouldClose();}

    };

}