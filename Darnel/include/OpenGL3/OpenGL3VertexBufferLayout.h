#pragma once

#include "Shader.h"
#include "VertexBufferLayout.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    struct OpenGL3VertexBufferElement : public VertexBufferElement {
        OpenGL3VertexBufferElement(const std::string &name, ShaderDataType type, unsigned int count, bool normalized)
            : VertexBufferElement(name, type, count, normalized) {

            switch (type) {
                case ShaderDataType::None:
                    DARNEL_ASSERT(false, "None is an invalid shader type.");
                    break;

                case ShaderDataType::Float:
                    size = count * 4;
                    break;

                case ShaderDataType::UnsignedInt:
                    size = count * 4;
                    break;

                case ShaderDataType::UnsignedByte:
                    size = count * 1;
                    break;

                default:
                    DARNEL_ASSERT(false, "Unknown shader type.");
            }
        }
    };

    class OpenGL3VertexBufferLayout: public VertexBufferLayout {
    public:
        OpenGL3VertexBufferLayout() {}
        ~OpenGL3VertexBufferLayout() override {}

        virtual void Push(const std::string &name, ShaderDataType type, unsigned int count, bool normalized = false) override;
    };
}
