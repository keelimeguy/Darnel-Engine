#include "TestSprite.h"

#include "Darnel.h"
#include "Sprite.h"
#include "Texture.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    const int TestSprite::s_NumSettings = 0;
    const char* TestSprite::s_Settings[] = {""};

    TestSprite::TestSprite(int i) {
        m_texture = darnel::MakeTexture("resources/textures/star.png");
        m_star1 = darnel::MakeSprite(270.0f, 190.0f, 100.0f, 100.0f, m_texture);
        m_star2 = darnel::MakeSprite(25.0f, 25.0f, 50.0f, 50.0f, m_texture);
        m_color1 = darnel::MakeSprite(50.0f, 50.0f, 50.0f, 50.0f, darnel::MakeTexture(255, 255, 0, 100));
        m_color2 = darnel::MakeSprite(565.0f, 25.0f, 50.0f, 50.0f, darnel::MakeTexture(255, 0, 255));

        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        m_proj_view = proj * view;
    }

    void TestSprite::OnRender() {
        m_star1->Draw(m_proj_view);
        m_star2->Draw(m_proj_view);
        m_color1->Draw(m_proj_view);
        m_color2->Draw(m_proj_view);
    }

    void TestSprite::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
