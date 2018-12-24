#pragma once

#include "Test.h"

#include "Sprite.h"
#include "Texture.h"

#include <memory>

namespace test {
    class TestSprite : public Test {
    public:
        TestSprite();

        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::mat4 m_proj_view;
        std::unique_ptr<::darnel::Sprite> m_star1, m_star2, m_color1, m_color2;
        std::shared_ptr<::darnel::Texture> m_texture;
    };
}
