#pragma once

#include "CoreFramework.h"
#include "Window.h"

namespace darnel {
    class OpenGL3Framework : public CoreFramework {
    public:
        Window* Init(int width, int height, std::string name) override;
        void Terminate() override;
        Window* CreateWindow(int width, int height, std::string name) override;
        bool WindowLoop(Window* window) override;

        void ImGuiInit(Window* window) override;
        void ImGuiNewFrame() override;
        void ImGuiRenderDrawData(ImDrawData* drawData) override;
        void ImGuiShutdown() override;
    };
}
