#pragma once

namespace darnel {
    class Window {
    public:
        bool IsValid() { return m_valid; }

        virtual void MakeActive() = 0;
        virtual void Clear(float f0, float f1, float f2, float f3) = 0;
    protected:
        bool m_valid = false;
    };
}
