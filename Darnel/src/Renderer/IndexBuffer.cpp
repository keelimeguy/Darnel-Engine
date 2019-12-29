#include "IndexBuffer.h"
#include "OpenGL3IndexBuffer.h"

#include "Renderer.h"

namespace darnel {
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const unsigned int *data, unsigned int count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<IndexBuffer>(new OpenGL3IndexBuffer(data, count));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
