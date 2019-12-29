#include "Window.h"
#include "OpenGL3Window.h"

#include "Renderer.h"

namespace darnel {
    std::shared_ptr<Window> Window::Create(std::string name, unsigned int width, unsigned int height) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<Window>(new OpenGL3Window(name, width, height));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
