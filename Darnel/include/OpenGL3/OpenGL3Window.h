#pragma once

#include "Window.h"
#include "GraphicsContext.h"

struct GLFWwindow;

namespace darnel {
    class OpenGL3Window : public Window {
    public:
        OpenGL3Window(std::string name, unsigned int width, unsigned int height);
        ~OpenGL3Window();

        void OnUpdate() override;
        void Focus() override;
        void Close() override;

        virtual void *GetNativeWindow() const { return m_Window; }

    private:
        struct GLFWwindow *m_Window;
        GraphicsContext *m_Context;
    };
}
