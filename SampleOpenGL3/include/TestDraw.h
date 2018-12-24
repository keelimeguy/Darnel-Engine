#pragma once

#include "Test.h"

#include "OpenGL3Lib/Renderer.h"
#include "OpenGL3Lib/VertexBufferLayout.h"

#include <memory>

namespace test {
    class TestDraw : public Test {
    public:
        TestDraw();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::vec3 m_translation;
        float m_r, m_increment;

        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
        std::unique_ptr<IndexBuffer> m_ib;
        std::unique_ptr<Shader> m_shader;
    };
}
