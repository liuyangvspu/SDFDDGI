#include "ShaderProgram.h"


namespace gip{


    uint32_t ShaderProgram::_loadShader(const char* fileName, int type){
        uint32_t shaderID;
		std::string shaderSrc;
		FileLoaderFactory::loadTextFromFile(fileName, shaderSrc);

		const char* shaderSrcChar = shaderSrc.c_str();
        shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSrcChar, NULL);
		glCompileShader(shaderID);
		{
			int  success;
			char infoLog[512];
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                std::string shaderType;
                if(type == GL_VERTEX_SHADER) shaderType = "VERTEX";
                else if(type == GL_FRAGMENT_SHADER) shaderType = "FRAGMENT";
                else if(type == GL_GEOMETRY_SHADER) shaderType = "GEOMETRY";
                else{
					ERROR("SHADER::{} TYPE_UNKNOWN - TYPE = {}", shaderType.c_str(), type);
				}
				ERROR("SHADER::{} COMPILATION FAILED - TYPE = {}", shaderType.c_str(), type);
			}
		}

        return shaderID;

    }

    void ShaderProgram::loadShader(const char* vertexFile, const char* fragmentFile){
        uint32_t vid = _loadShader(vertexFile, SHADER_TYPE_VERTEX);
        uint32_t fid = _loadShader(fragmentFile, SHADER_TYPE_FRAGMENT);


        _shaderProgram = glCreateProgram();

		glAttachShader(_shaderProgram, vid);
		glAttachShader(_shaderProgram, fid);
		glLinkProgram(_shaderProgram);

		{
			int  success;
			char infoLog[512];
			glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
				ERROR("ERROR::SHADER::COMP::LINKING_FAILED\t{}", infoLog);
				assert(false);
			}
		}


		LOG("Loaded Shader '{}' and '{}'", vertexFile, fragmentFile);

    }


    void ShaderProgram::uniform_set1Integer(const char* name, int32_t value){
        int id = _check_uniform_(name, true);
        glUniform1i(id, value);
        GLenum error = glGetError();
		if(error != GL_NO_ERROR){
			ERROR("OpenGL Error 'uniform_set1Integer' : {}", error);
		}
        
    }

    void ShaderProgram::uniform_set1Float(const char* name, float value){
  		int id = _check_uniform_(name, true);
        glUniform1fv(id, 1, &value);
        GLenum error = glGetError();
		if(error != GL_NO_ERROR){
			ERROR("OpenGL Error 'uniform_set1float' : {}", error);
		}

	}

	void ShaderProgram::uniform_set1Mat4(const char* name, const float* value){
  		int id = _check_uniform_(name, true);
        glUniformMatrix4fv(id, 1, GL_FALSE, value);
        GLenum error = glGetError();
		if(error != GL_NO_ERROR){
			ERROR("OpenGL Error 'uniform_set1Mat4' : {}", error);
		}

	}



}