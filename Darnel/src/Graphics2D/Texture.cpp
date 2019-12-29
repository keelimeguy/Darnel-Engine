#include "Texture.h"
#include "OpenGL3Texture.h"

#include "Renderer.h"

namespace darnel {
    std::shared_ptr<Texture> Texture::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<Texture>(new OpenGL3Texture(path));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

    std::shared_ptr<Texture> Texture::Create(unsigned char *buffer, int width, int height, int bpp) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<Texture>(new OpenGL3Texture(buffer, width, height, bpp));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

    std::shared_ptr<Texture> Texture::Create(unsigned char r, unsigned char g, unsigned char b) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<Texture>(new OpenGL3Texture(r, g, b));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

    std::shared_ptr<Texture> Texture::Create(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::OpenGL3: return std::shared_ptr<Texture>(new OpenGL3Texture(r, g, b, a));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
