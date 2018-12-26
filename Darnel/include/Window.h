#pragma once

#include "Event.h"
#include <functional>

namespace darnel {
    class Window {
    public:
        bool IsValid() { return m_valid; }

        virtual void MakeActive() = 0;
        virtual void Clear(float f0, float f1, float f2, float f3) = 0;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
    protected:
        bool m_valid = false;
    };
}
