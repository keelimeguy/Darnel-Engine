#pragma once

#include "Event.h"

namespace darnel {
    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "WindowResizeEvent"; };

        static EventType GetStaticType() { return EventType::WindowResize; }

    private:
        unsigned int m_Width, m_Height;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "WindowCloseEvent"; };

        static EventType GetStaticType() { return EventType::WindowClose; }
    };

    class WindowMovedEvent : public Event {
    public:
        WindowMovedEvent(int xOffset, int yOffset, int xPos, int yPos)
            : m_XOffset(xOffset), m_YOffset(yOffset), m_XPos(xPos), m_YPos(yPos) {}

        inline int GetXOffset() const { return m_XOffset; }
        inline int GetYOffset() const { return m_YOffset; }
        inline int GetXPos() const { return m_XPos; }
        inline int GetYPos() const { return m_YPos; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_XOffset << ", " << m_YOffset << " (to " << m_XPos << ", " << m_YPos << ")";
            return ss.str();
        }

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "WindowMovedEvent"; };

        static EventType GetStaticType() { return EventType::WindowMoved; }

    private:
        int m_XOffset, m_YOffset, m_XPos, m_YPos;
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() {}

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "WindowFocusEvent"; };

        static EventType GetStaticType() { return EventType::WindowFocus; }
    };

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent() {}

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "WindowLostFocusEvent"; };

        static EventType GetStaticType() { return EventType::WindowLostFocus; }
    };
}
