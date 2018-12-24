#include "OpenGL3Lib/Renderer.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    bool ret = true;
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << "):"
            << function << " " << file << ":" << line << std::endl;
        ret = false;
    }
    return ret;
}

void Renderer::Clear() const {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}