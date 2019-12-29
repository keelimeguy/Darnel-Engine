#include "OpenGL3Context.h"

#include "OpenGL3Renderer.h"

namespace darnel {
    OpenGL3Context::OpenGL3Context(GLFWwindow *window)
        : m_Window(window) {
        DARNEL_ASSERT(m_Window, "GLFW window is NULL.");
    }

    void OpenGL3Context::Init() {
        glfwMakeContextCurrent(m_Window);
    }

    void OpenGL3Context::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}
