#pragma once

#include "Test.h"

#include "Camera.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"

namespace test {
    class TestSprite : public Test {
    public:
        TestSprite(int i = 0);

        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char* s_Settings[];

    private:
        std::shared_ptr<darnel::Camera> m_camera;
        std::shared_ptr<darnel::Entity> m_star1, m_star2, m_color1, m_color2;
        std::shared_ptr<darnel::Texture> m_texture;
    };
}
