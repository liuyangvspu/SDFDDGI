#include "ShaderParser.h"

namespace gip{

    const char* ShaderParser::getShaderSource(const char* filePath){
        std::vector<const char*> includes{};
		std::string shaderSrc;
		FileLoaderFactory::loadTextFromFile(filePath, shaderSrc);
        std::size_t location = shaderSrc.find("#include");
        while(location != std::string::npos){
            std::size_t start = shaderSrc.find("\"", location);
            std::size_t end = shaderSrc.find("\"", start+1);
            std::string include = shaderSrc.substr(start + 1, (end - start - 1));
            LOG("Trying to append '{}'", include);

		    std::string appendedShaderSrc;
            std::string appendFileLocation = GIP_INTERNAL_SHADER("") + include;
		    FileLoaderFactory::loadTextFromFile(appendFileLocation.c_str(), appendedShaderSrc);

            shaderSrc = shaderSrc.substr(0, location) + appendedShaderSrc + shaderSrc.substr(end+1);


            location = shaderSrc.find("#include");
            
        }
        return shaderSrc.c_str();

    }


}