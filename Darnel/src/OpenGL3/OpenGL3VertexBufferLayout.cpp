#include "OpenGL3VertexBufferLayout.h"
#include <vector>

namespace darnel {
    void OpenGL3VertexBufferLayout::PushFloat(unsigned int count) {
        m_Elements.push_back(new OpenGL3VertexBufferElement(GL_FLOAT, count, GL_FALSE));
        m_Stride += count * m_Elements[0]->GetSizeOfType(GL_FLOAT);
    }

    void OpenGL3VertexBufferLayout::PushInt(unsigned int count) {
        m_Elements.push_back(new OpenGL3VertexBufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
        m_Stride += count * m_Elements[0]->GetSizeOfType(GL_UNSIGNED_INT);
    }

    void OpenGL3VertexBufferLayout::PushByte(unsigned int count) {
        m_Elements.push_back(new OpenGL3VertexBufferElement(GL_UNSIGNED_BYTE, count, GL_TRUE));
        m_Stride += count * m_Elements[0]->GetSizeOfType(GL_UNSIGNED_BYTE);
    }
}
