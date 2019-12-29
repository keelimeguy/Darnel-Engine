#include "OpenGL3VertexBufferLayout.h"
#include <vector>

namespace darnel {
    void OpenGL3VertexBufferLayout::Push(const std::string &name, ShaderDataType type, unsigned int count, bool normalized) {
        OpenGL3VertexBufferElement *element = new OpenGL3VertexBufferElement(name, type, count, normalized);
        m_Elements.push_back(std::shared_ptr<OpenGL3VertexBufferElement>(element));
        m_Stride += element->size;
    }
}
