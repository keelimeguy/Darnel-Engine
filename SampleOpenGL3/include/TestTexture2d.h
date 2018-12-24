#pragma once

#include "Test.h"

#include "OpenGL3Lib/Renderer.h"
#include "OpenGL3Lib/VertexBufferLayout.h"
#include "OpenGL3Lib/Texture.h"

#include <memory>

namespace test {
    class TestTexture2d : public Test {
    public:
        TestTexture2d();

        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::vec3 m_translation;

        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
        std::unique_ptr<IndexBuffer> m_ib;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_texture;
    };
}
