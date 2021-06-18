#pragma once
#include <string>
#include <fstream>
#include <streambuf>
#include <Engine/src/Utils/Logger.h>



#define GIP_INTERNAL(x)         "src/Resources/" x
#define GIP_INTERNAL_SHADER(x)  GIP_INTERNAL("Shaders/") x
#define GIP_INTERNAL_TEXTURE(x) GIP_INTERNAL("Textures/") x
#define GIP_INTERNAL_MODEL(x)   GIP_INTERNAL("Models/") x
#define GIP_INTERNAL_SOUNDS(x)  GIP_INTERNAL("Sounds/") x


namespace gip {

    namespace FileLoaderFactory{
        extern void loadTextFromFile(const char fileName[], std::string& dst);
        //rgba default composition
        extern unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, bool vert_flip = true, int req_comp = 4/*STBI_rgb_alpha = 4*/);
        extern void free(void* data);
    }
}