#include "OpenGL3Renderer.h"
#include <iostream>

namespace darnel {
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

    void OpenGL3Renderer::Clear() const {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void OpenGL3Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const OpenGL3Shader & shader) const {
        shader.Bind();
        va.Bind();
        ib.Bind();

        GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}
