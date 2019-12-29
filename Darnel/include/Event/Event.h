#pragma once

#include "Core.h"

namespace darnel {
    enum EventType {
        None = 0, KeyPressed, KeyReleased, KeyTyped, AppTick, AppUpdate, AppRender,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        MouseEnter, MouseLeave, WindowClose, WindowResize, WindowFocus,
        WindowLostFocus, WindowMoved
    };

    class Event {
    public:
        bool inline IsHandled() const { return m_Handled; }

        virtual EventType GetEventType() const = 0;
        virtual const char *GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }

    protected:
        bool m_Handled = false;

    private:
        friend class EventDispatcher;
    };

    class EventDispatcher {
    public:
        EventDispatcher(Event &event) : m_Event(event) {}

        template<typename T>
        bool Dispatch(std::function<bool(T &)> listener) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_Handled = listener(*(T *)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };
}
