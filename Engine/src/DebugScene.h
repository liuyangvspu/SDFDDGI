#pragma once
#include <glad/glad.h>
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Renderer/ShaderParser.h>
#include <Engine/src/Renderer/ShaderProgram.h>

namespace gip{

    class DebugScene{
        private:
            ShaderProgram _shader;
        public:
            void load();
            void update();
            void render();
            void unload();
    };

}