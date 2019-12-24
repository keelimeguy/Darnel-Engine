#pragma once

#include "Test.h"

namespace test {
    class TestMultiWindow : public Test {
    public:
        TestMultiWindow(int i = 0);
        ~TestMultiWindow();

        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char *s_Settings[];

    private:
        std::weak_ptr<darnel::Window> m_OrigWindow;
        std::weak_ptr<darnel::Window> m_NewWindow;
    };
}
