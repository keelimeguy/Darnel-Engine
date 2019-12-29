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

    class OpenGL3Renderer : public Renderer {
    public:
        static GLFWwindow *Init(std::string name, unsigned int width, unsigned int height);

        void Clear(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f) override;
        void Terminate(std::vector<std::shared_ptr<Window>> *windows = nullptr) override;
        void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) override;
    };
}
