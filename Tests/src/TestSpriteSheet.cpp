#include "TestSpriteSheet.h"

#include "SpriteSheet.h"
#include "Sprite.h"

#include "Darnel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    const int TestSpriteSheet::s_NumSettings = 2;
    const char* TestSpriteSheet::s_Settings[] = {"All", "One"};

    TestSpriteSheet::TestSpriteSheet(int setting)
        : m_slices(24), m_sprites(m_slices*m_slices)
    {
        m_sheet = std::make_unique<darnel::SpriteSheet>("resources/textures/star.png", m_slices, m_slices);

        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        m_proj_view = proj * view;

        float x = 640.0f/m_slices;
        float y = 480.0f/m_slices;
        float w = 640.0f/(m_slices+2);
        float h = 480.0f/(m_slices+2);
        switch (setting) {
            case 1:
            {
                std::shared_ptr<darnel::Texture> tex = m_sheet->GrabTexture(0, 0);
                for (int j = 0; j < m_slices; ++j)
                    for (int i = 0; i < m_slices; ++i)
                        m_sprites[i+j*m_slices] = darnel::Sprite::Create(x*i, y*j, w, h, tex);
                break;
            }

            default:
            {
                for (int j = 0; j < m_slices; ++j)
                    for (int i = 0; i < m_slices; ++i)
                        m_sprites[i+j*m_slices] = darnel::Sprite::Create(x*i, y*j, w, h, m_sheet->GrabTexture(i, j));
            }
        }
    }

    void TestSpriteSheet::OnRender() {
        darnel::Renderer::Clear();
        for (int i = 0; i < m_slices*m_slices; ++i)
            m_sprites[i]->Draw(m_proj_view);
    }

    void TestSpriteSheet::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
