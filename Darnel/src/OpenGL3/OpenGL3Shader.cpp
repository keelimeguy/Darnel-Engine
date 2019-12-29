#include "OpenGL3Shader.h"
#include "OpenGL3Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace darnel {

    OpenGL3Shader::OpenGL3Shader(const ShaderProgramSource &shaderSrc)
        : Shader(shaderSrc) {

        m_RendererID = CreateShader(shaderSrc.VertexSource, shaderSrc.FragmentSource);
    }

    OpenGL3Shader::OpenGL3Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath)
        : Shader(vertexFilePath, fragmentFilePath) {

        ShaderProgramSource source = ParseShader(vertexFilePath, fragmentFilePath);
        m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    }

    OpenGL3Shader::OpenGL3Shader(const std::string &filePath)
        : Shader(filePath) {

        ShaderProgramSource source = ParseShader(filePath);
        m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    }

    OpenGL3Shader::~OpenGL3Shader() {
        GLCALL(glDeleteProgram(m_RendererID));
    }

    unsigned int OpenGL3Shader::CompileShader(unsigned int type, const std::string &source) {
        GLCALL(unsigned int id = glCreateShader(type));
        const char *src = source.c_str();
        GLCALL(glShaderSource(id, 1, &src, nullptr));
        GLCALL(glCompileShader(id));

        int result;
        GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE) {
            int length;
            GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char *message = (char *)alloca(length * sizeof(char));
            GLCALL(glGetShaderInfoLog(id, length, &length, message));
            std::cout << length << ": " << message << std::endl << std::flush;
            GLCALL(glDeleteShader(id));
            if (type == GL_VERTEX_SHADER)
                DARNEL_ASSERT(false, "Could not compile vertex shader!");
            else if (type == GL_FRAGMENT_SHADER)
                DARNEL_ASSERT(false, "Could not compile fragment shader!");
            else
                DARNEL_ASSERT(false, "Could not compile shader!");
        }

        return id;
    }

    unsigned int OpenGL3Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
        GLCALL(unsigned int program = glCreateProgram());
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        GLCALL(glAttachShader(program, vs));
        GLCALL(glAttachShader(program, fs));
        GLCALL(glLinkProgram(program));
        GLCALL(glValidateProgram(program));

        int result;
        GLCALL(glGetProgramiv(program, GL_LINK_STATUS, &result));
        if (result == GL_FALSE) {
            int length;
            GLCALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
            char *message = (char *)alloca(length * sizeof(char));
            GLCALL(glGetProgramInfoLog(program, length, &length, message));
            std::cout << length << ": " << message << std::endl << std::flush;
            GLCALL(glDeleteShader(vs));
            GLCALL(glDeleteShader(fs));
            GLCALL(glDeleteProgram(program));
            DARNEL_ASSERT(false, "Could not link shaders!");
        }

        GLCALL(glDetachShader(program, vs));
        GLCALL(glDetachShader(program, fs));

        return program;
    }

    int OpenGL3Shader::GetUniformLocation(const std::string &name) {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
            return m_UniformLocationCache[name];
        }

        GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
        if (location == -1) {
            std::cout << "Warning: Uniform " << name << " not found." << std::endl;
        }
        m_UniformLocationCache[name] = location;
        return location;
    }

    void OpenGL3Shader::SetUniform1i(const std::string &name, int i0) {
        GLCALL(glUniform1i(GetUniformLocation(name), i0));
    }

    void OpenGL3Shader::SetUniformMat4f(const std::string &name, const glm::mat4 m0) {
        GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m0[0][0]));
    }

    void OpenGL3Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
        GLCALL(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
    }

    void OpenGL3Shader::Bind() const {
        GLCALL(glUseProgram(m_RendererID));
    }

    void OpenGL3Shader::Unbind() const {
        GLCALL(glUseProgram(0));
    }
}
