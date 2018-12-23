#include "TestClearColor.h"

#include "Darnel.h"
#include <imgui.h>

namespace test {
    TestClearColor::TestClearColor()
        : m_clearColor{ 0.2f, 0.3f, 0.8f, 1.0f } {
    }

    void TestClearColor::OnRender() {
        darnelClear(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    }

    void TestClearColor::OnImGuiRender() {
        ImGui::ColorEdit4("Clear Color", m_clearColor);
    }
}
