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

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Width; }
        inline unsigned int GetHeight() const override { return m_Height; }
        inline unsigned int GetXPos() const { return m_XPos; }
        inline unsigned int GetYPos() const { return m_YPos; }

        void MakeActive() override;
        void Clear(float f0, float f1, float f2, float f3) override;

        inline void SetEventCallback(const std::function<void(Event&)>& callback) override {
            m_EventCallback = callback;
        }

    private:
        struct GLFWwindow* m_window;
        int m_Width, m_Height, m_XPos, m_YPos;
        std::function<void(Event&)> m_EventCallback;

        friend class OpenGL3Framework;
    };
}
