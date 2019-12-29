#pragma once

#include "Window.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace darnel {
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL3
        };

        inline static API GetAPI() { return s_API; }

        static std::shared_ptr<RendererAPI> Create();

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4 &color) = 0;
        virtual void SetClearColor(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f) = 0;
        virtual void Clear() = 0;

        virtual void Draw(const VertexArray &va, const IndexBuffer &ib) = 0;

    private:
        static API s_API;
    };

    class Renderer {
    public:
        static Renderer *Get();

        Renderer() { m_RendererAPI = RendererAPI::Create(); }

        inline std::shared_ptr<RendererAPI> GetRendererAPI() { return m_RendererAPI; }

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        virtual void Submit(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) {
            shader.Bind();
            m_RendererAPI->Draw(va, ib);
        }

        virtual void BeginScene() = 0;
        virtual void EndScene() = 0;
        virtual void Terminate(std::vector<std::shared_ptr<Window>> *windows = nullptr) = 0;

    private:
        std::shared_ptr<RendererAPI> m_RendererAPI;
    };

    class RenderCommand {
    public:
        inline static void Init() {
            Renderer::Get()->GetRendererAPI()->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            Renderer::Get()->GetRendererAPI()->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4 &color) {
            Renderer::Get()->GetRendererAPI()->SetClearColor(color);
        }

        inline static void SetClearColor(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f) {
            Renderer::Get()->GetRendererAPI()->SetClearColor(f0, f1, f2, f3);
        }

        inline static void Clear() {
            Renderer::Get()->GetRendererAPI()->Clear();
        }

        inline static void Draw(const VertexArray &va, const IndexBuffer &ib) {
            Renderer::Get()->GetRendererAPI()->Draw(va, ib);
        }
    };
}
