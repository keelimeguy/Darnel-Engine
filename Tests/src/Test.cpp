#include "Test.h"

namespace test {
    const int Test::s_NumSettings = 0;
    const char *Test::s_Settings[] = {""};

    TestMenu::TestMenu(Test *&currentTest)
        : m_CurrentTest(currentTest)
    {}

    void TestMenu::OnRender() {
        darnel::RenderCommand::Clear();
    }

    void TestMenu::OnImGuiRender() {
        Test::OnImGuiRender();
        for (auto &test : m_Tests) {
            if (ImGui::Button(test->Name().c_str())) {
                m_CurrentTest = test->Callback()(test->m_choice);
                auto wnd = darnel::Application::Get()->GetWindow().lock();
                wnd->Focus();
            }
            if (test->NumSettings()) {
                ImGui::SameLine();
                std::stringstream ss;
                ss << "##Setting: " << test->Name();
                ImGui::Combo(ss.str().c_str(), &(test->m_choice), test->Settings(), test->NumSettings());
            }
        }
    }
}
