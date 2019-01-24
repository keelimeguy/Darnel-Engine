#pragma once

#include "Test.h"

#include "Entity.h"

namespace test {
    class TestCamera : public Test {
    public:
        TestCamera(int i = 0);

        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char* s_Settings[];

    private:
        std::shared_ptr<darnel::Entity> m_star;

        // Camera parameters
        float m_left = 0.0f, m_right = 500.0f,
            m_bottom = 0.0f, m_top = 500.0f,
            m_near = -1.0f, m_far = 1.0f;
        float m_x = 0.0f, m_y = 0.0f, m_z = 0.0f;
    };
}
