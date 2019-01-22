#include "OpenGL3Window.h"

#include "OpenGL3Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Event.h"
#include "WindowEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

namespace darnel {
    static bool s_GLFWInitialized = false;

    Window* Window::Create(std::string name, unsigned int width, unsigned int height) {
        return new OpenGL3Window(name, width, height);
    }

    OpenGL3Window::OpenGL3Window(std::string name, unsigned int width, unsigned int height)
        : Window(name, width, height)
    {
        if (s_GLFWInitialized) {
            m_Window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        } else {
            m_Window = OpenGL3Renderer::Init(name, width, height);
            s_GLFWInitialized = true;
        }

        DARNEL_ASSERT(m_Window, "GLFW window creation failed.");

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1); // set VSync

        glfwGetWindowPos(m_Window, &m_XPos, &m_YPos);
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* wnd, int width, int height) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);
            window.m_Width = width;
            window.m_Height = height;

            WindowResizeEvent event(width, height);
            window.m_EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* wnd) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);
            WindowCloseEvent event;
            window.m_EventCallback(event);
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* wnd, int xPos, int yPos) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);
            int xOffset = xPos - window.m_XPos;
            int yOffset = yPos - window.m_YPos;
            window.m_XPos = xPos;
            window.m_YPos = yPos;
            WindowMovedEvent event(xOffset, yOffset, xPos, yPos);
            window.m_EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* wnd, int focused) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            switch (focused) {
                case GLFW_TRUE:
                {
                    WindowFocusEvent event;
                    window.m_EventCallback(event);
                    break;
                }
                case GLFW_FALSE:
                {
                    WindowLostFocusEvent event;
                    window.m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* wnd, int key, int scancode, int action, int mods) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    window.m_EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    window.m_EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    window.m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* wnd, unsigned int key) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            KeyTypedEvent event(key);
            window.m_EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* wnd, int button, int action, int mods) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    window.m_EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    window.m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* wnd, double xOffset, double yOffset) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            window.m_EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* wnd, double xPos, double yPos) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            MouseMovedEvent event((float)xPos, (float)yPos);
            window.m_EventCallback(event);
        });

        glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* wnd, int entered) {
            OpenGL3Window& window = *(OpenGL3Window*)glfwGetWindowUserPointer(wnd);

            if (entered) {
                MouseEnterEvent event;
                window.m_EventCallback(event);
            } else {
                MouseLeaveEvent event;
                window.m_EventCallback(event);
            }
        });
    }

    OpenGL3Window::~OpenGL3Window() {
        glfwDestroyWindow(m_Window);
    }

    void OpenGL3Window::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void OpenGL3Window::Close() {
        WindowCloseEvent event;
        m_EventCallback(event);
    }

    // void OpenGL3Window::MakeActiveContext() {
    //     glfwMakeContextCurrent(m_Window);
    //     // glfwSwapInterval(1);
    // }

    void OpenGL3Window::Focus() {
        glfwFocusWindow(m_Window);
    }
}
