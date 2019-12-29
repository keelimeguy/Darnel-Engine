#pragma once

#include <vector>
#include <memory>

namespace darnel {
    struct VertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
            : type(type), count(count), normalized(normalized) {}
        virtual unsigned int GetSizeOfType(unsigned int type) const = 0;
    };

    class VertexBufferLayout {
    protected:
        std::vector<VertexBufferElement *> m_Elements;
        unsigned int m_Stride;

    public:
        VertexBufferLayout() : m_Stride(0) {}
        virtual ~VertexBufferLayout() {}

        virtual void PushFloat(unsigned int count) = 0;
        virtual void PushInt(unsigned int count) = 0;
        virtual void PushByte(unsigned int count) = 0;

        inline std::vector<VertexBufferElement *> GetElements() const { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }

        static std::shared_ptr<VertexBufferLayout> Create();
    };
}
