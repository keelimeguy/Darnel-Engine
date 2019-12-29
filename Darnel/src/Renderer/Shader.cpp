#include "Shader.h"
#include "OpenGL3Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace darnel {
    std::shared_ptr<Shader> Shader::Create(const ShaderProgramSource &shaderSrc) {
        return std::shared_ptr<Shader>(new OpenGL3Shader(shaderSrc));
    }

    std::shared_ptr<Shader> Shader::Create(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
        return std::shared_ptr<Shader>(new OpenGL3Shader(vertexFilePath, fragmentFilePath));
    }

    std::shared_ptr<Shader> Shader::Create(const std::string &filePath) {
        return std::shared_ptr<Shader>(new OpenGL3Shader(filePath));
    }

    ShaderProgramSource Shader::ParseShader(const std::string &filePath) {
        std::ifstream stream(filePath);

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            } else {
                ss[(int)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    ShaderProgramSource Shader::ParseShader(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
        std::string line;

        std::stringstream vertexShader;
        std::ifstream vertexStream(vertexFilePath);
        while (getline(vertexStream, line)) {
            vertexShader << line << '\n';
        }

        std::stringstream fragmentShader;
        std::ifstream fragmentStream(fragmentFilePath);
        while (getline(fragmentStream, line)) {
            fragmentShader << line << '\n';
        }

        return {vertexShader.str(), fragmentShader.str()};
    }
}
