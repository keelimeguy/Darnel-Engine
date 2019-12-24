#pragma once

#include "Window.h"

namespace darnel {
    class Renderer {
    public:
        static void Clear(float f0 = 0.0f, float f1 = 0.0f, float f2 = 0.0f, float f3 = 1.0f);
        static void Terminate(std::vector<std::shared_ptr<Window>> *windows = nullptr);
    };
}
