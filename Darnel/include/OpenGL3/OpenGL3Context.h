#pragma once

#include "GraphicsContext.h"

struct GLFWwindow;

namespace darnel {
    class OpenGL3Context : public GraphicsContext {
    public:
        OpenGL3Context(GLFWwindow *window);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_Window;
    };
}
