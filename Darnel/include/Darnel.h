#pragma once

struct ImDrawData;

int darnelInit();
void darnelTerminate();
void darnelClear(float f0, float f1, float f2, float f3);
bool darnelLoopDone();

void ImGui_Darnel_Init();
void ImGui_Darnel_NewFrame();
void ImGui_Darnel_RenderDrawData(ImDrawData* drawData);
void ImGui_Darnel_Shutdown();
