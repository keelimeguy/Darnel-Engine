#pragma once

struct ImDrawData;

namespace darnel {
    int DarnelInit();
    void DarnelTerminate();
    void DarnelClear(float f0, float f1, float f2, float f3);
    bool DarnelLoopDone();

    void ImGui_Darnel_Init();
    void ImGui_Darnel_NewFrame();
    void ImGui_Darnel_RenderDrawData(ImDrawData* drawData);
    void ImGui_Darnel_Shutdown();
}
