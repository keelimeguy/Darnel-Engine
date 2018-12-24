#pragma once

#include <string>

struct ImDrawData;

namespace darnel {
    bool DarnelInit(int width, int height, std::string name);
    bool DarnelCreateWindow(int width, int height, std::string name);
    void DarnelTerminate();
    bool DarnelWindowLoop();
    void DarnelClearWindow(float f1, float f2, float f3, float f4);

    void ImGui_Darnel_Init();
    void ImGui_Darnel_NewFrame();
    void ImGui_Darnel_RenderDrawData(ImDrawData* drawData);
    void ImGui_Darnel_Shutdown();
}
