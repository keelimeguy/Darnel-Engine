#pragma once

#include <glm\glm.hpp>

#include <string>
#include <memory>
#include <unordered_map>

namespace darnel {
    enum class ShaderDataType {
        None = 0,
        Float,
        UnsignedInt,
        UnsignedByte
    };

    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class Shader {
    public:
        static std::shared_ptr<Shader> Create(const ShaderProgramSource &shaderSrc);
        static std::shared_ptr<Shader> Create(const std::string &vertexFilePath, const std::string &fragmentFilePath);
        static std::shared_ptr<Shader> Create(const std::string &filePath);

        Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath) {}
        Shader(const std::string &filePath) {}
        Shader(const ShaderProgramSource &shaderSrc) {}
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetUniform1i(const std::string &name, int i0) = 0;
        virtual void SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3) = 0;
        virtual void SetUniformMat4f(const std::string &name, const glm::mat4 m0) = 0;

    protected:
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        static ShaderProgramSource ParseShader(const std::string &vertexFilePath, const std::string &fragmentFilePath);
        static ShaderProgramSource ParseShader(const std::string &filePath);
        virtual unsigned int CompileShader(unsigned int type, const std::string &source) = 0;
        virtual unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader) = 0;

        virtual int GetUniformLocation(const std::string &name) = 0;
    };
}
