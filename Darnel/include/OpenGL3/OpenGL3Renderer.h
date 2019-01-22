#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core.h"

#define ASSERT(x) DARNEL_ASSERT(x, "")
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


#include "VertexArray.h"
#include "IndexBuffer.h"
#include "OpenGL3Shader.h"

namespace darnel {
    bool GLLogCall(const char* function, const char* file, int line);
    void GLClearError();

    class OpenGL3Renderer {
    public:
        static GLFWwindow* Init(std::string name, unsigned int width, unsigned int height);
        static void Terminate();
        static void Clear(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f);
        static void Draw(const VertexArray& va, const IndexBuffer& ib, const OpenGL3Shader& shader);
    };
}