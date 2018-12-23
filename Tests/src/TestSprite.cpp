#include "TestSprite.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    TestSprite::TestSprite()
        : m_star1(270, 190, 100, 100, "resources/textures/star.png"),
          m_star2(25, 25, 50, 50, "resources/textures/star.png")
    {
        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        m_proj_view = proj * view;
    }

    void TestSprite::OnRender() {
        m_star1.Draw(m_proj_view);
        m_star2.Draw(m_proj_view);
    }

    void TestSprite::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
