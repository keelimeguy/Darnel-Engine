#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core.h"

#define ASSERT(x) DARNEL_ASSERT(x, "")
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#include "Renderer.h"

#include "OpenGL3VertexArray.h"
#include "OpenGL3VertexBuffer.h"
#include "OpenGL3VertexBufferLayout.h"
#include "OpenGL3IndexBuffer.h"
#include "OpenGL3Shader.h"

namespace darnel {
    bool GLLogCall(const char *function, const char *file, int line);
    void GLClearError();

    class OpenGL3RendererAPI : public RendererAPI {
    public:
        void Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void SetClearColor(const glm::vec4 &color) override;
        void SetClearColor(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f) override;
        void Clear() override;

        void Draw(const VertexArray &va, const IndexBuffer &ib) override;
    };

    class OpenGL3Renderer : public Renderer {
    public:
        OpenGL3Renderer() {}

        static GLFWwindow *Init(std::string name, unsigned int width, unsigned int height);

        void BeginScene() override;
        void EndScene() override;
        void Terminate(std::vector<std::shared_ptr<Window>> *windows = nullptr) override;
    };
}
