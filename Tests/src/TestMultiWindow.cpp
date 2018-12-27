#include "TestMultiWindow.h"

#include "Darnel.h"
#include <imgui.h>

namespace test {
    const int TestMultiWindow::s_NumSettings = 0;
    const char* TestMultiWindow::s_Settings[] = {""};

    TestMultiWindow::TestMultiWindow(int i) {
        m_OrigWindow = darnel::GetActiveWindow();
        darnel::CreateWindow(480, 480, "New Window");
        darnel::SetWindowContext(m_OrigWindow);
    }

    TestMultiWindow::~TestMultiWindow() {
        darnel::CloseWindow("New Window");
    }

    void TestMultiWindow::OnRender() {
        if (darnel::SetWindowContext("New Window", true)) {
            darnel::ClearWindow(0.5f,0.0f,0.5f,1.0f);
            darnel::Flush();
        }

        darnel::SetWindowContext(m_OrigWindow);
        darnel::ClearWindow(0.5f,0.5f,0.0f,1.0f);
    }

    void TestMultiWindow::OnImGuiRender() {
    }
}
