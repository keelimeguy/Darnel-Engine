#include "Darnel.h"

#include "Test.h"
#include "TestSprite.h"
#include "TestClearColor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include <iostream>

int main() {
    if (darnelInit())
        return -1;
    {
        ImGui::CreateContext();
        ImGui_Darnel_Init();

        ImGui::StyleColorsDark();

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestSprite>("Sprite");

        while (!darnelLoopDone()) {
            darnelClear(0.0f, 0.0f, 0.0f, 1.0f);

            ImGui_Darnel_NewFrame();
            ImGui::NewFrame();

            if (currentTest) {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_Darnel_RenderDrawData(ImGui::GetDrawData());
        }

        if (currentTest != testMenu)
            delete testMenu;
        delete currentTest;
    }

    ImGui_Darnel_Shutdown();
    ImGui::DestroyContext();

    darnelTerminate();
    return 0;
}
