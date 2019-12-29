#include "OpenGL3VertexBuffer.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    OpenGL3VertexBuffer::OpenGL3VertexBuffer(const void *data, unsigned int size)
        : VertexBuffer(data, size) {

        GLCALL(glCreateBuffers(1, &m_RendererID));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    OpenGL3VertexBuffer::~OpenGL3VertexBuffer() {
        GLCALL(glDeleteBuffers(1, &m_RendererID));
    }

    void OpenGL3VertexBuffer::Bind() const {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void OpenGL3VertexBuffer::Unbind() const {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}
