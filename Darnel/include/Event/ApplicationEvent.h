#pragma once

#include "Event.h"

namespace darnel {
    class AppTickEvent : public Event {
    public:
        AppTickEvent() {}

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "AppTickEvent"; };

        static EventType GetStaticType() { return EventType::AppTick; }
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "AppUpdateEvent"; };

        static EventType GetStaticType() { return EventType::AppUpdate; }
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}

        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char *GetName() const override { return "AppRenderEvent"; };

        static EventType GetStaticType() { return EventType::AppRender; }
    };
}
