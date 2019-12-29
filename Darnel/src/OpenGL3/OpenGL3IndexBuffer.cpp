#include "OpenGL3IndexBuffer.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    OpenGL3IndexBuffer::OpenGL3IndexBuffer(const unsigned int *data, unsigned int count)
        : IndexBuffer(data, count) {

        GLCALL(glCreateBuffers(1, &m_RendererID));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }

    OpenGL3IndexBuffer::~OpenGL3IndexBuffer() {
        GLCALL(glDeleteBuffers(1, &m_RendererID));
    }

    void OpenGL3IndexBuffer::Bind() const {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void OpenGL3IndexBuffer::Unbind() const {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}
