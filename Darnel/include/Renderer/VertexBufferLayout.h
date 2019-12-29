#pragma once

#include "Shader.h"

#include <vector>
#include <string>
#include <memory>

namespace darnel {
    struct VertexBufferElement {
        ShaderDataType type;
        unsigned int size;
        unsigned int count;
        bool normalized;

        VertexBufferElement(const std::string &name, ShaderDataType type, unsigned int count, bool normalized)
            : type(type), size(0), count(count), normalized(normalized) {}
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout() : m_Stride(0) {}
        virtual ~VertexBufferLayout() {}

        virtual void Push(const std::string &name, ShaderDataType type, unsigned int count, bool normalized = false) = 0;

        inline std::vector<std::shared_ptr<VertexBufferElement>> GetElements() const { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }

        static std::shared_ptr<VertexBufferLayout> Create();

    protected:
        std::vector<std::shared_ptr<VertexBufferElement>> m_Elements;
        unsigned int m_Stride;
    };
}
