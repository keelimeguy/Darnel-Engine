#include "Renderer.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    static OpenGL3Renderer *s_OpenGL3Instance = nullptr;
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL3;

    std::shared_ptr<RendererAPI> RendererAPI::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::API::OpenGL3: return std::shared_ptr<RendererAPI>(new OpenGL3RendererAPI());
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

    Renderer *Renderer::Get() {
        switch (GetAPI()) {
            case RendererAPI::API::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;

            case RendererAPI::API::OpenGL3:
                if (!s_OpenGL3Instance) s_OpenGL3Instance = new OpenGL3Renderer();
                return s_OpenGL3Instance;
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
