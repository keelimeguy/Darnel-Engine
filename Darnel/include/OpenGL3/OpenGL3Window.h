#pragma once

#include "Window.h"
#include "OpenGL3Framework.h"

#include <memory>

struct GLFWwindow;

namespace darnel {
    class OpenGL3Window : public Window {
    public:
        OpenGL3Window(int width, int height, std::string name);
        ~OpenGL3Window() {}

        void MakeActive() override;
        void Clear(float f0, float f1, float f2, float f3) override;
    private:
        struct GLFWwindow* m_window;

        friend class OpenGL3Framework;
    };
}
