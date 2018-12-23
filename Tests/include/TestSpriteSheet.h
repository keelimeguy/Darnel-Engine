#pragma once

#include "Test.h"

#include "SpriteSheet.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <memory>

namespace test {
    class TestSpriteSheet : public Test {
    public:
        TestSpriteSheet();

        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::mat4 m_proj_view;
        SpriteSheet m_sheet;
        std::shared_ptr<Sprite> m_corners[4];
    };
}
