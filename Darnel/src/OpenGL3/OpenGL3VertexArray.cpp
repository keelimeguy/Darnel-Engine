#include "OpenGL3VertexArray.h"
#include "OpenGL3Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace darnel {
    OpenGL3VertexArray::OpenGL3VertexArray() {
        GLCALL(glCreateVertexArrays(1, &m_RendererId));
    }

    OpenGL3VertexArray::~OpenGL3VertexArray() {
        GLCALL(glDeleteVertexArrays(1, &m_RendererId));
    }

    void OpenGL3VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
        Bind();
        vb.Bind();
        const auto &elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); ++i) {
            const auto &element = elements[i];
            GLCALL(glEnableVertexAttribArray(i));
            GLCALL(glVertexAttribPointer(i, element->count, element->type, element->normalized, layout.GetStride(),
                                         (const void *)(uintptr_t)offset));
            offset += element->count * element->GetSizeOfType(element->type);
        }
    }

    void OpenGL3VertexArray::Bind() const {
        GLCALL(glBindVertexArray(m_RendererId));
    }

    void OpenGL3VertexArray::Unbind() const {
        GLCALL(glBindVertexArray(0));
    }
}
