#pragma once

#include "Event.h"

namespace darnel {
    class AppTickEvent : public Event {
    public:
        AppTickEvent() {}

        static EventType GetStaticType() { return EventType::AppTick; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "AppTickEvent"; };
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}

        static EventType GetStaticType() { return EventType::AppUpdate; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "AppUpdateEvent"; };
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}

        static EventType GetStaticType() { return EventType::AppRender; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "AppRenderEvent"; };
    };
}
