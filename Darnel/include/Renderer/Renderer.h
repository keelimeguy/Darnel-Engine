#pragma once

#include "Window.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace darnel {
    enum class RendererAPI {
        None = 0,
        OpenGL3
    };

    class Renderer {
    private:
        static RendererAPI s_RendererAPI;
    public:
        static Renderer *Get();
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

        virtual void Clear(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f) = 0;
        virtual void Terminate(std::vector<std::shared_ptr<Window>> *windows = nullptr) = 0;
        virtual void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) = 0;
    };
}
