#pragma once

#include "Event.h"
#include <functional>
#include <string>

namespace darnel {
    class Window {
    public:
        Window(int width, int height, std::string name)
            : m_Name(name), m_Width(width), m_Height(height) {}
        virtual ~Window() {}

        bool IsValid() { return m_Valid; }

        virtual void MakeActiveContext() = 0;
        virtual void SetFocus() = 0;
        virtual void Close() = 0;

        virtual void Clear(float f0, float f1, float f2, float f3) = 0;
        virtual void OnRender() = 0;

        virtual inline std::string GetName() const { return m_Name; }
        virtual inline unsigned int GetWidth() const { return m_Width; }
        virtual inline unsigned int GetHeight() const { return m_Height; }
        virtual inline unsigned int GetXPos() const { return m_XPos; }
        virtual inline unsigned int GetYPos() const { return m_YPos; }

        virtual inline void SetEventCallback(const std::function<void(Event&)>& callback) {
            m_EventCallback = callback;
        }

    protected:
        bool m_Valid = false;

        std::string m_Name;
        int m_Width, m_Height, m_XPos, m_YPos;
        std::function<void(Event&)> m_EventCallback;
    };
}
