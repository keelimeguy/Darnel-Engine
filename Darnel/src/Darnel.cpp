#include "CoreFramework.h"
#include "OpenGL3Framework.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include <iostream>
#include <memory>

static std::unique_ptr<darnel::CoreFramework> gs_Framework = std::make_unique<darnel::OpenGL3Framework>();
static darnel::Window* gs_curWindow;

namespace darnel {
    bool Init(int width, int height, std::string name) {
        Window* window = gs_Framework->Init(width, height, name);
        if (window == NULL) {
            gs_Framework->Terminate();
            return false;
        }

        if (!window->IsValid()) return false;
        gs_curWindow = window;
        return true;
    }

    bool CreateWindow(int width, int height, std::string name) {
        Window* window = gs_Framework->CreateWindow(width, height, name);
        if (!window->IsValid()) return false;

        gs_curWindow = window;
        gs_curWindow->MakeActive();
        return true;
    }

    void Terminate() {
        return gs_Framework->Terminate();
    }

    bool WindowLoop() {
        return gs_Framework->WindowLoop(gs_curWindow);
    }

    void ClearWindow(float f1, float f2, float f3, float f4) {
        gs_curWindow->Clear(f1, f2, f3, f4);
    }

    void ImGui_Init() {
        gs_Framework->ImGuiInit(gs_curWindow);
    }

    void ImGui_NewFrame() {
        gs_Framework->ImGuiNewFrame();
    }

    void ImGui_RenderDrawData(ImDrawData* drawData) {
        gs_Framework->ImGuiRenderDrawData(drawData);
    }

    void ImGui_Shutdown() {
        gs_Framework->ImGuiShutdown();
    }
}
