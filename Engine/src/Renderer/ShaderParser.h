#pragma once
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Utils/Files/FileLoaderFactory.h>
#include <vector>
namespace gip{

    class ShaderParser{
        public:
            static const char* getShaderSource(const char* filePath);

    };

}