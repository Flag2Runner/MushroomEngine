#include "Rendering/Shader.h"
#include "config.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>

namespace mr
{
    Shader::Shader(const std::string &vertexShaderName, const std::string &fragmentShadername)
        : mShaderProgramId{0}
    {
        unsigned int vertexShader = CompileShader(vertexShaderName, GL_VERTEX_SHADER);
        unsigned int fragmentShader = CompileShader(fragmentShadername, GL_FRAGMENT_SHADER);

    }
    unsigned int Shader::CompileShader(const std::string &shaderName, unsigned int shaderType)
    {
        std::string ShaderStr = ReadShader(shaderName);
        std::cout << "read shader: \n" << ShaderStr << std::endl;

        unsigned int shaderId = glCreateShader(shaderType);

        const char* shaderCStr = ShaderStr.c_str();
        glShaderSource(shaderId, 1, &shaderCStr, nullptr);
        glCompileShader(shaderId);

        int success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::string shaderTypeStr = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
            throw std::runtime_error("ERROR::SHADER::" + shaderTypeStr + "::COMPILATION_FAIL:\n" + std::string(infoLog));
        }

        std::cout << "Shader compilation successfil!" << std::endl;
        return shaderId;
    }

    std::string Shader::ReadShader(const std::string &shaderName) const
    {
        std::ifstream fileStream{GetProjectDir() + "shaders/" + shaderName + ".glsl"};
        
        std::ostringstream buffer;
        buffer << fileStream.rdbuf();

        return buffer.str();
    }

}