#pragma once
#include <stdint.h>
#include <string>
#include <cassert>
#include <Engine/src/Utils/Logger.h>
#include <Engine/src/Utils/Files/FileLoaderFactory.h>
#include <Engine/src/Renderer/ShaderParser.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define SHADER_TYPE_VERTEX      (int) 0x8B31
#define SHADER_TYPE_FRAGMENT    (int) 0x8B30
#define SHADER_TYPE_GEOMETRY    (int) 0x8DD9
#define SHADER_TYPE_TESSELATION (uint8_t)GL_arb_tesselation_shader

namespace gip{

    class ShaderProgram{
        
        private:
            uint32_t _loadShader(const char* fileName, int type);
            uint32_t _shaderProgram;

            inline int _check_uniform_(const char* name, bool print = true){
                GLint uniformID = glGetUniformLocation(_shaderProgram, name);
                if(uniformID == -1 && print){
                    WARN("'{}' name not found in shader.", name);
                }
                return uniformID;
            }
        public:
            ShaderProgram() = default;
            void loadShader(const char* vertexFile, const char* fragFile);
            void loadShader(const char* vertexFile, const char* fragFile, const char* geomFile);

            inline void use(){glUseProgram(_shaderProgram);}


            void uniform_set1Integer(const char* name, int32_t value);
            void uniform_set1Float(const char* name, float value);
            void uniform_set1Mat4(const char* name, const float* value);


    };



}