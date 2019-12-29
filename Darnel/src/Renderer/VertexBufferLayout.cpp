#include "VertexBufferLayout.h"
#include "OpenGL3VertexBufferLayout.h"

#include "Renderer.h"

namespace darnel {
    std::shared_ptr<VertexBufferLayout> VertexBufferLayout::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::API::OpenGL3: return std::shared_ptr<VertexBufferLayout>(new OpenGL3VertexBufferLayout());
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
