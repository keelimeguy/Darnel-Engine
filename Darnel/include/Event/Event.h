#pragma once

#include <functional>
#include <string>

namespace darnel {
    enum EventType {
        None = 0, KeyPressed, KeyReleased, AppTick, AppUpdate, AppRender,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        MouseEnter, MouseLeave, WindowClose, WindowResize, WindowFocus,
        WindowLostFocus, WindowMoved
    };

    class Event {
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }
    protected:
        bool m_Handled = false;
    private:
        friend class EventDispatcher;
    };

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : m_Event(event) {}

        template<typename T>
        bool Dispatch(std::function<bool(T&)> listener) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_Handled = listener(*(T*)&m_Event);
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };
}
