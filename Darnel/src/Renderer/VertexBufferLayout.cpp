#include "VertexBufferLayout.h"
#include "OpenGL3VertexBufferLayout.h"

namespace darnel {
    std::shared_ptr<VertexBufferLayout> VertexBufferLayout::Create() {
        return std::shared_ptr<VertexBufferLayout>(new OpenGL3VertexBufferLayout());
    }
}
