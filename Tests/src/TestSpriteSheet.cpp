#include "TestSpriteSheet.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    TestSpriteSheet::TestSpriteSheet()
        : m_sheet("resources/textures/star.png", 3, 3)
    {
        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        m_proj_view = proj * view;

        m_corners[0] = m_sheet.MakeSprite(0, 0, 100, 100, 0, 0);
        m_corners[1] = m_sheet.MakeSprite(150, 0, 100, 100, 1, 0);
        m_corners[2] = m_sheet.MakeSprite(0, 150, 100, 100, 1, 2);
        m_corners[3] = m_sheet.MakeSprite(150, 150, 100, 100, 2, 2);
    }

    void TestSpriteSheet::OnRender() {
        for (int i = 0; i < 4; i++)
            m_corners[i]->Draw(m_proj_view);
    }

    void TestSpriteSheet::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
