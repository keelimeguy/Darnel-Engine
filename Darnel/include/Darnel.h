#pragma once

#include <string>

struct ImDrawData;

namespace darnel {
    bool Init(int width, int height, std::string name);
    bool CreateWindow(int width, int height, std::string name);
    void Terminate();
    bool WindowLoop();
    void ClearWindow(float f1, float f2, float f3, float f4);

    void ImGui_Init();
    void ImGui_NewFrame();
    void ImGui_RenderDrawData(ImDrawData* drawData);
    void ImGui_Shutdown();
}
