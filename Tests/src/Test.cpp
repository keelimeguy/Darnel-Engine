#include "Test.h"

namespace test {
    const int Test::s_NumSettings = 0;
    const char* Test::s_Settings[] = {""};

    TestMenu::TestMenu(Test*& currentTest)
        : m_CurrentTest(currentTest)
    {}

    void TestMenu::OnRender() {
        darnel::Renderer::Clear();
    }

    void TestMenu::OnImGuiRender() {
        for (auto& test : m_Tests) {
            if (ImGui::Button(test->Name().c_str()))
                m_CurrentTest = test->Callback()(test->m_choice);
            if (test->NumSettings()) {
                ImGui::SameLine();
                ImGui::Combo("Setting", &(test->m_choice), test->Settings(), test->NumSettings());
            }
        }
    }
}
