#include "OpenGL3Sprite.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "OpenGL3Shader.h"

#include <glm/glm.hpp>

#include <sstream>

namespace darnel {
    std::unique_ptr<IndexBuffer> OpenGL3Sprite::SpriteContext::s_ib;
    std::unique_ptr<OpenGL3Shader> OpenGL3Sprite::SpriteContext::s_shader;
    std::unordered_map<std::string, std::weak_ptr<OpenGL3Sprite::SpriteContext>> OpenGL3Sprite::s_contextCache;

    std::shared_ptr<Sprite> Sprite::Create(float width, float height, std::shared_ptr<Texture> texture) {
        return std::shared_ptr<Sprite>(new OpenGL3Sprite(width, height, texture));
    }

    OpenGL3Sprite::SpriteContext::SpriteContext(float width, float height)
        : m_width(width), m_height(height) {
        if (!s_ib) {
            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };
            s_ib = std::make_unique<IndexBuffer>(indices, 6);
        }

        if (!s_shader) {
            s_shader = std::make_unique<OpenGL3Shader>("resources/shaders/Texture.shader");
        }

        float positions[] = {
            0.0f, 0.0f, 0.0f, 0.0f,    // 0
            width, 0.0f, 1.0f, 0.0f,   // 1
            width, height, 1.0f, 1.0f, // 2
            0.0f, height, 0.0f, 1.0f,  // 3
        };

        m_vb = std::make_unique<VertexBuffer>(positions, 4 * 4 * (unsigned int) sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_va = std::make_unique<VertexArray>();
        m_va->AddBuffer(*m_vb, layout);
    }

    void OpenGL3Sprite::InitContext(float width, float height) {
        std::stringstream name;
        name << width << "," << height;
        if (s_contextCache.find(name.str()) != s_contextCache.end())
            if (m_context = s_contextCache[name.str()].lock())
                return;

        m_context = std::make_shared<SpriteContext>(width, height);
        s_contextCache[name.str()] = m_context;
    }

    OpenGL3Sprite::OpenGL3Sprite(float width, float height, std::shared_ptr<Texture> texture)
        : Sprite(width, height, texture) {
        InitContext(width, height);
    }

    OpenGL3Sprite::~OpenGL3Sprite() {
        std::stringstream name;
        name << m_context->m_width << "," << m_context->m_height;
        m_context = nullptr;

        if (!s_contextCache[name.str()].lock())
            s_contextCache.erase(name.str());
    }

    void OpenGL3Sprite::Draw(const glm::mat4 &mvp) {
        OpenGL3Renderer renderer;

        m_texture->Bind();

        m_context->s_shader->Bind();
        m_context->s_shader->SetUniform1i("u_Texture", 0);
        m_context->s_shader->SetUniformMat4f("u_MVP", mvp);

        m_context->m_vb->Bind();
        renderer.Draw(*(m_context->m_va), *(m_context->s_ib), *(m_context->s_shader));
    }
}
