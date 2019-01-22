#include "TestClearColor.h"

#include "Darnel.h"

namespace test {
    const int TestClearColor::s_NumSettings = 0;
    const char* TestClearColor::s_Settings[] = {""};

    TestClearColor::TestClearColor(int i)
        : m_clearColor{ 0.2f, 0.3f, 0.8f, 1.0f } {
    }

    void TestClearColor::OnRender() {
        darnel::OpenGL3Renderer::Clear(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    }

    void TestClearColor::OnImGuiRender() {
        ImGui::ColorEdit4("Clear Color", m_clearColor);
    }
}