#include "TestLevel.h"

#include "Darnel.h"

namespace test {
    const int TestLevel::s_NumSettings = 0;
    const char *TestLevel::s_Settings[] = {""};

    TestLevel::TestLevel(int i) {
        float width = 640.0f;
        float height = 480.0f;
        auto camera = std::make_shared<PlayerCamera>(0.0f, width, 0.0f, height);

        m_level = std::make_shared<Level>();

        auto static_layer = m_level->GetStaticEntityLayer();
        static_layer->PushEntity(std::make_shared<darnel::Entity>(
                                     width / 2.0f - 5.0f,
                                     height / 2.0f - 5.0f,
                                     darnel::Sprite::Create(10.0f, 10.0f, darnel::Texture::Create("resources/textures/star.png")))
                                );
        static_layer->SetCamera(camera);

        auto entity_layer = m_level->GetEntityLayer();
        entity_layer->PushEntity(std::make_shared<darnel::Entity>(200.0f, 200.0f, darnel::Sprite::Create(100.0f, 100.0f,
                                 darnel::Texture::Create("resources/textures/star.png"))));
        entity_layer->SetCamera(camera);

        auto camera_layer = m_level->GetCameraLayer();
        camera_layer->SetCamera(camera);
    }

    void TestLevel::OnUpdate() {
        m_level->OnUpdate();
    }

    void TestLevel::OnEvent(darnel::Event &e) {
        m_level->OnEvent(e);
    }
}
