#pragma once

#include "Window.h"

struct GLFWwindow;

namespace darnel {
    class OpenGL3Window : public Window {
    public:
        OpenGL3Window(std::string name, unsigned int width, unsigned int height);
        ~OpenGL3Window();

        void OnUpdate() override;
        void Focus() override;
        void Close() override;

    private:
        struct GLFWwindow *m_Window;
    };
}
