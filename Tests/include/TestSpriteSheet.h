#pragma once

#include "Test.h"

#include "SpriteSheet.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace test {
    class TestSpriteSheet : public Test {
    public:
        TestSpriteSheet();

        void OnRender() override;
        void OnImGuiRender() override;
    private:
        int m_slices;
        glm::mat4 m_proj_view;
        std::unique_ptr<darnel::SpriteSheet> m_sheet;
        std::vector<std::unique_ptr<darnel::Sprite>> m_sprites;
    };
}
