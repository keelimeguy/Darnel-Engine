#pragma once

#include "Event.h"

namespace darnel {
    class KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

    protected:
        KeyEvent(int keycode) : m_KeyCode(keycode) {}
        int m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (repeat:" << m_RepeatCount << ")";
            return ss.str();
        }

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "KeyPressedEvent"; };

        static EventType GetStaticType() { return EventType::KeyPressed; }

    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "KeyReleasedEvent"; };

        static EventType GetStaticType() { return EventType::KeyReleased; }
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "KeyTypedEvent"; };

        static EventType GetStaticType() { return EventType::KeyTyped; }
    };
}
