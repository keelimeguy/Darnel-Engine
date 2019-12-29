#include "TestSprite.h"

#include "Camera.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"

#include "Darnel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    const int TestSprite::s_NumSettings = 0;
    const char *TestSprite::s_Settings[] = {""};

    TestSprite::TestSprite(int i) {
        m_texture = darnel::Texture::Create("resources/textures/star.png");
        m_star1 = std::make_shared<darnel::Entity>(270.0f, 190.0f, darnel::Sprite::Create(100.0f, 100.0f, m_texture));
        m_star2 = std::make_shared<darnel::Entity>(25.0f, 25.0f, darnel::Sprite::Create(50.0f, 50.0f, m_texture));
        m_color1 = std::make_shared<darnel::Entity>(50.0f, 50.0f, darnel::Sprite::Create(50.0f, 50.0f,
                   darnel::Texture::Create(255, 255, 0, 100)));
        m_color2 = std::make_shared<darnel::Entity>(565.0f, 25.0f, darnel::Sprite::Create(50.0f, 50.0f,
                   darnel::Texture::Create(255, 0, 255)));

        m_camera = darnel::MakeOrthographicCamera(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    }

    void TestSprite::OnRender() {
        auto proj_view = m_camera->GetProjView();
        darnel::RenderCommand::Clear();
        m_star1->Draw(proj_view);
        m_star2->Draw(proj_view);
        m_color1->Draw(proj_view);
        m_color2->Draw(proj_view);
    }
}
