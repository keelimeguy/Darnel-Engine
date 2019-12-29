#include "VertexBuffer.h"
#include "OpenGL3VertexBuffer.h"

#include "Renderer.h"

namespace darnel {
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void *data, unsigned int size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<VertexBuffer>(new OpenGL3VertexBuffer(data, size));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
