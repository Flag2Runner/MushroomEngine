#include "Rendering/Shader.h"
#include "config.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace mr
{
    Shader::Shader(const std::string &vertexShaderName, const std::string &fragmentShadername)
        : mShaderProgramId{0}
    {
        unsigned int vertexShader = CompileShader(vertexShaderName, GL_VERTEX_SHADER);
        unsigned int fragmentShader = CompileShader(fragmentShadername, GL_FRAGMENT_SHADER);

        mShaderProgramId = BuildShaderProgram(vertexShader, fragmentShader);

    }

    void Shader::UseShaderProgram()
    {
        glUseProgram(mShaderProgramId);
    }

    void Shader::SetUniformMat4(const std::string &uniformName, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(mShaderProgramId, uniformName.c_str()),
        1,
        GL_FALSE, 
        glm::value_ptr(matrix));
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

    unsigned int Shader::BuildShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId)
    {
        unsigned int newShaderProgram = glCreateProgram();
        glAttachShader(newShaderProgram, vertexShaderId);
        glAttachShader(newShaderProgram, fragmentShaderId);
        glLinkProgram(newShaderProgram);

        int success;
        glGetProgramiv(newShaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(newShaderProgram, 512, NULL, infoLog);

            throw std::runtime_error("ERROR::SHADER::SHADER_PROGRAM::LINK_FAILED:\n" + std::string(infoLog));
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        return newShaderProgram;
    }
}