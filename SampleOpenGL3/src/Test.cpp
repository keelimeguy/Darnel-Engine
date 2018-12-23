#include "Test.h"
#include <imgui.h>

namespace test {
    TestMenu::TestMenu(Test*& currentTest)
        : m_currentTest(currentTest) {
    }

    void TestMenu::OnImGuiRender() {
        for (auto& test : m_Tests) {
            if (ImGui::Button(test.first.c_str()))
                m_currentTest = test.second();
        }
    }
}
