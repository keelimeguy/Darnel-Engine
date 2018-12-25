#pragma once

#include <glm\glm.hpp>

#include <string>
#include <unordered_map>

namespace darnel {
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class OpenGL3Shader {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        OpenGL3Shader(const std::string& filePath);
        ~OpenGL3Shader();

        void Bind() const;
        void Unbind() const;

        void SetUniform1i(const std::string& name, int i0);
        void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
        void SetUniformMat4f(const std::string& name, const glm::mat4 m0);

    private:
        ShaderProgramSource ParseShader(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        int GetUniformLocation(const std::string& name);
    };
}
