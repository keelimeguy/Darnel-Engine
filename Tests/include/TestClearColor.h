#pragma once

#include "Test.h"

namespace test {
    class TestClearColor : public Test {
    public:
        TestClearColor(int i = 0);

        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char *s_Settings[];

    private:
        float m_clearColor[4];
    };
}
