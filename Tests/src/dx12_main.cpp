#include "DirectX12Framework.h"
#include "DirectX12Renderer.h"

#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include <iostream>

int main() {
    darnel::DirectX12Framework framework;
    darnel::Window* window = framework.Init(640, 480, "Darnel Window");
    if (!window) return -1;
    {
        ImGui::CreateContext();
        framework.ImGuiInit(window);

        ImGui::StyleColorsDark();

        while (framework.WindowLoop(window)) {
            BeginRender();

            framework.ImGuiNewFrame();
            ImGui::NewFrame();

            ImGui::Button("<-");

            ImGui::Render();
            framework.ImGuiRenderDrawData(ImGui::GetDrawData());

            EndRender();
        }
    }

    framework.ImGuiShutdown();
    ImGui::DestroyContext();

    framework.Terminate();
    return 0;
}
