#include "TestCamera.h"

#include "Camera.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"

#include "Darnel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    const int TestCamera::s_NumSettings = 0;
    const char *TestCamera::s_Settings[] = {""};

    TestCamera::TestCamera(int i) {
        m_star = std::make_shared<darnel::Entity>(200.0f, 200.0f, darnel::Sprite::Create(100.0f, 100.0f,
                 darnel::Texture::Create("resources/textures/star.png")));
    }

    void TestCamera::OnRender() {
        auto camera = darnel::MakeOrthographicCamera(m_left, m_right, m_bottom, m_top, m_near, m_far);
        camera->MoveTo(m_x, m_y, m_z);

        darnel::RenderCommand::Clear();
        m_star->Draw(camera->GetProjView());
    }

    void TestCamera::OnImGuiRender() {
        Test::OnImGuiRender();

        ImGui::SliderFloat("Camera Left", &m_left, 0.0f, 1000.0f, "%.3f");
        ImGui::SliderFloat("Camera Right", &m_right, 0.0f, 1000.0f, "%.3f");
        ImGui::SliderFloat("Camera Bottom", &m_bottom, 0.0f, 1000.0f, "%.3f");
        ImGui::SliderFloat("Camera Top", &m_top, 0.0f, 1000.0f, "%.3f");
        ImGui::SliderFloat("Camera Near", &m_near, -2.0f, 2.0f, "%.3f");
        ImGui::SliderFloat("Camera Far", &m_far, -2.0f, 2.0f, "%.3f");

        ImGui::SliderFloat("Camera X", &m_x, -500.0f, 500.0f, "%.3f");
        ImGui::SliderFloat("Camera Y", &m_y, -500.0f, 500.0f, "%.3f");
        ImGui::SliderFloat("Camera Z", &m_z, -2.0f, 2.0f, "%.3f");
    }
}
