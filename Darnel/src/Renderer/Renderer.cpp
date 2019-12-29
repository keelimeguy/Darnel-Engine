#include "Renderer.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    static OpenGL3Renderer *s_OpenGL3Instance = nullptr;
    RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL3;

    Renderer *Renderer::Get() {
        switch (GetAPI()) {
            case RendererAPI::None:
                DARNEL_ASSERT(false, "None is not a valid RendererAPI.");
                return nullptr;

            case RendererAPI::OpenGL3:
                if (!s_OpenGL3Instance) s_OpenGL3Instance = new OpenGL3Renderer();
                return s_OpenGL3Instance;
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
