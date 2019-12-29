#include "VertexBuffer.h"
#include "OpenGL3VertexBuffer.h"

namespace darnel {
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void *data, unsigned int size) {
        return std::shared_ptr<VertexBuffer>(new OpenGL3VertexBuffer(data, size));
    }
}
