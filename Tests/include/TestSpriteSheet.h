#pragma once

#include "Test.h"

#include "SpriteSheet.h"
#include "Entity.h"

#include <glm/glm.hpp>

namespace test {
    class TestSpriteSheet : public Test {
    public:
        TestSpriteSheet(int setting = 0);

        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char *s_Settings[];

    private:
        int m_slices;
        glm::mat4 m_proj_view;
        std::unique_ptr<darnel::SpriteSheet> m_sheet;
        std::vector<std::shared_ptr<darnel::Entity>> m_entities;
    };
}
