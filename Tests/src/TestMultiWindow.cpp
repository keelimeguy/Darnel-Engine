#include "TestMultiWindow.h"

#include "Darnel.h"

namespace test {
    const int TestMultiWindow::s_NumSettings = 0;
    const char *TestMultiWindow::s_Settings[] = {""};

    TestMultiWindow::TestMultiWindow(int i) {
        auto app = darnel::Application::Get();
        auto wnd = app->GetWindow().lock();
        DARNEL_ASSERT(wnd, "Couldn't find window");
        m_NewWindow = app->NewChildWindow(wnd.get(), "New Window", 480, 480);
    }

    TestMultiWindow::~TestMultiWindow() {
        if (auto wnd = m_NewWindow.lock()) {
            wnd->Close();
        }
    }

    void TestMultiWindow::OnRender() {
        darnel::Renderer::Get()->Clear(0.5f, 0.0f, 0.5f, 1.0f);
    }
}
