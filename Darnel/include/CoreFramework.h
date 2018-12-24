#pragma once

#include <vector>
#include <memory>

#include "Window.h"

struct ImDrawData;

namespace darnel {
    class CoreFramework {
    public:
        virtual Window* Init(int width, int height, std::string name) = 0;
        virtual void Terminate() = 0;
        virtual Window* CreateWindow(int width, int height, std::string name) = 0;
        virtual bool WindowLoop(Window* window) = 0;

        virtual void ImGuiInit(Window* window) = 0;
        virtual void ImGuiNewFrame() = 0;
        virtual void ImGuiRenderDrawData(ImDrawData* drawData) = 0;
        virtual void ImGuiShutdown() = 0;
    protected:
        std::vector<std::unique_ptr<Window>> m_windows;
    };
}
