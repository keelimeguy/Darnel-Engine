#pragma once

#include "Test.h"

#include "Sprite.h"

namespace test {
    class TestSprite : public Test {
    public:
        TestSprite();

        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::mat4 m_proj_view;
        Sprite m_star1, m_star2;
    };
}
