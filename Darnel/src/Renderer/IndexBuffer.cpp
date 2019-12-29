#include "IndexBuffer.h"
#include "OpenGL3IndexBuffer.h"

namespace darnel {
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const unsigned int *data, unsigned int count) {
        return std::shared_ptr<IndexBuffer>(new OpenGL3IndexBuffer(data, count));
    }
}
