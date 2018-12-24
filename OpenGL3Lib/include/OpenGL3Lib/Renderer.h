#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#include "OpenGL3Lib/VertexArray.h"
#include "OpenGL3Lib/IndexBuffer.h"
#include "OpenGL3Lib/Shader.h"

bool GLLogCall(const char* function, const char* file, int line);
void GLClearError();

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const;
};
