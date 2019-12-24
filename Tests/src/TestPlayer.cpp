#include "TestPlayer.h"

#include "Camera.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"

#include "Darnel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    const int TestPlayer::s_NumSettings = 2;
    const char *TestPlayer::s_Settings[] = {"Fixed Camera", "Fixed Player"};

    TestPlayer::TestPlayer(int i) {
        m_fixPlayer = (i == 1);
        m_x = 320.0;
        m_y = 240.0;
        if (m_fixPlayer) {
            m_player = std::make_shared<Player>(m_x, m_y, darnel::Sprite::Create(100.0f, 100.0f,
                                                darnel::Texture::Create("resources/textures/star.png")));
            m_camera = std::make_shared<PlayerCamera>();
        } else {
            m_player = std::make_shared<Player>(590.0f, 430.0f, darnel::Sprite::Create(100.0f, 100.0f,
                                                darnel::Texture::Create("resources/textures/star.png")));
            m_camera = std::make_shared<PlayerCamera>();
        }
    }

    void TestPlayer::OnUpdate() {
        if (m_fixPlayer) m_player->MoveTo(m_x, m_y, m_z);
        else m_camera->MoveTo(m_x, m_y, m_z);

        m_player->OnUpdate();
        m_camera->OnUpdate();
    }

    void TestPlayer::OnEvent(darnel::Event &e) {
        if (m_fixPlayer) m_camera->OnEvent(e);
        else m_player->OnEvent(e);
    }

    void TestPlayer::OnRender() {
        auto proj_view = m_camera->GetProjView();
        darnel::Renderer::Clear();
        m_player->Draw(proj_view);
    }

    void TestPlayer::OnImGuiRender() {
        Test::OnImGuiRender();

        if (m_fixPlayer) {
            ImGui::SliderFloat("Player X", &m_x, 0.0f, 640.0f, "%.3f");
            ImGui::SliderFloat("Player Y", &m_y, 0.0f, 480.0f, "%.3f");
            ImGui::SliderFloat("Player Z", &m_z, -2.0f, 2.0f, "%.3f");
        } else {
            ImGui::SliderFloat("Camera X", &m_x, 0.0f, 640.0f, "%.3f");
            ImGui::SliderFloat("Camera Y", &m_y, 0.0f, 480.0f, "%.3f");
            ImGui::SliderFloat("Camera Z", &m_z, -2.0f, 2.0f, "%.3f");
        }
    }
}
