#pragma once

#include "Window.h"
#include "OpenGL3Framework.h"

#include <memory>
#include <functional>

struct GLFWwindow;

namespace darnel {
    class OpenGL3Window : public Window {
    public:
        OpenGL3Window(int width, int height, std::string name);
        ~OpenGL3Window();

        void OnRender() override;
        void Clear(float f0, float f1, float f2, float f3) override;

        void MakeActiveContext() override;
        void SetFocus() override;
        void Close() override;

    private:
        struct GLFWwindow* m_Window;

        friend class OpenGL3Framework;
    };
}
