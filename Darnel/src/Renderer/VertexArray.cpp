#include "VertexArray.h"
#include "OpenGL3VertexArray.h"

namespace darnel {
    std::shared_ptr<VertexArray> VertexArray::Create() {
        return std::shared_ptr<VertexArray>(new OpenGL3VertexArray());
    }
}
