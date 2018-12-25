#include "OpenGL3Window.h"

#include "OpenGL3Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace darnel {
    OpenGL3Window::OpenGL3Window(int width, int height, std::string name)
    {
        m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        m_valid = (m_window != NULL);
    }

    void OpenGL3Window::MakeActive() {
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1);
    }

    void OpenGL3Window::Clear(float f0, float f1, float f2, float f3) {
        GLCALL(glClearColor(f0, f1, f2, f3));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }
}
