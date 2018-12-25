#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
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
        void Clear() const;
        void Draw(const VertexArray & va, const IndexBuffer & ib, const OpenGL3Shader & shader) const;
    };
}
