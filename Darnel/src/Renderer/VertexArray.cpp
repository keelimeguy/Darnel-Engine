#include "VertexArray.h"
#include "OpenGL3VertexArray.h"

#include "Renderer.h"

namespace darnel {
    std::shared_ptr<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::API::OpenGL3: return std::shared_ptr<VertexArray>(new OpenGL3VertexArray());
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
