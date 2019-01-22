#pragma once

#include "Core.h"
#include "Event.h"

namespace darnel {
    class Window {
    public:
        static Window* Create( std::string name = "New Window",
            unsigned int width = 1280,
            unsigned int height = 720
        );

        Window(std::string name, unsigned int width, unsigned int height)
            : m_Name(name), m_Width(width), m_Height(height)
        {}

        virtual ~Window() {}

        virtual void OnUpdate() = 0;
        virtual void Focus() = 0;
        virtual void Close() = 0;

        virtual std::string GetName() const { return m_Name; }
        virtual unsigned int GetWidth() const { return m_Width; }
        virtual unsigned int GetHeight() const { return m_Height; }
        virtual unsigned int GetXPos() const { return m_XPos; }
        virtual unsigned int GetYPos() const { return m_YPos; }

        virtual void SetEventCallback(const std::function<void(Event&)>& callback) {
            m_EventCallback = callback;
        }

    protected:
        std::string m_Name;
        int m_Width, m_Height, m_XPos, m_YPos;
        std::function<void(Event&)> m_EventCallback;
    };
}
