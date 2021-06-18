#pragma once
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Utils/Input/InputManager.h>
#include <Engine/src/Utils/OpenGLWindow.h>
namespace gip{
    class Core{
        private:
            OpenGLWindow* _window;

        public:
            void load();
            void update();
            void render();
            void unload();



            inline bool shouldClose(){return false;}

    };
}