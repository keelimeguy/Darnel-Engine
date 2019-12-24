#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    VertexArray::VertexArray() {
        GLCALL(glGenVertexArrays(1, &m_RendererId));
    }

    VertexArray::~VertexArray() {
        GLCALL(glDeleteVertexArrays(1, &m_RendererId));
    }

    void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
        Bind();
        vb.Bind();
        const auto &elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); ++i) {
            const auto &element = elements[i];
            GLCALL(glEnableVertexAttribArray(i));
            GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                                         (const void *)(uintptr_t)offset));
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    void VertexArray::Bind() const {
        GLCALL(glBindVertexArray(m_RendererId));
    }

    void VertexArray::Unbind() const {
        GLCALL(glBindVertexArray(0));
    }
}
