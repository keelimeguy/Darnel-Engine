#pragma once

#include "Test.h"
#include <string>

namespace test {
    class TestMultiWindow : public Test {
    public:
        TestMultiWindow(int i = 0);
        ~TestMultiWindow();

        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char* s_Settings[];
    private:
        std::string m_OrigWindow;
    };
}