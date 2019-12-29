#pragma once

#include "Shader.h"

#include <glm\glm.hpp>

#include <string>

namespace darnel {
    class OpenGL3Shader: public Shader {
    public:
        OpenGL3Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath);
        OpenGL3Shader(const std::string &filePath);
        OpenGL3Shader(const ShaderProgramSource &shaderSrc);
        ~OpenGL3Shader();

        void Bind() const override;
        void Unbind() const override;

        void SetUniform1i(const std::string &name, int i0) override;
        void SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3) override;
        void SetUniformMat4f(const std::string &name, const glm::mat4 m0) override;

    protected:
        unsigned int CompileShader(unsigned int type, const std::string &source) override;
        unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader) override;

        int GetUniformLocation(const std::string &name) override;
    };
}
