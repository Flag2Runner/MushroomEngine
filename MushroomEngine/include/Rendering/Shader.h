#pragma once
#include <string>
#include <glm/glm.hpp>

namespace mr
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderName, const std::string& fragmentShadername);
        void UseShaderProgram();
        void SetUniformMat4(const std::string &uniformName, const glm::mat4 &matrix);

    private:
        unsigned int mShaderProgramId;
        unsigned int CompileShader(const std::string& shaderName, unsigned int shaderType);

        std::string ReadShader(const std::string& shaderName) const;

        unsigned int BuildShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);
    };
}
