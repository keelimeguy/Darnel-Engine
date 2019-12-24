#pragma once

#include "Test.h"

#include "Level.h"
#include "PlayerCamera.h"

namespace test {
    class TestLevel : public Test {
    public:
        TestLevel(int i = 0);

        void OnEvent(darnel::Event &e) override;
        void OnUpdate() override;

        static const int s_NumSettings;
        static const char *s_Settings[];

    private:
        std::shared_ptr<Level> m_level;
    };
}
