#include "Sprite.h"
#include "Texture.h"

#include "OpenGL3Lib/VertexArray.h"
#include "OpenGL3Lib/VertexBufferLayout.h"
#include "OpenGL3Lib/VertexBuffer.h"
#include "OpenGL3Lib/IndexBuffer.h"
#include "OpenGL3Lib/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sstream>

namespace darnel {
    std::unique_ptr<IndexBuffer> Sprite::SpriteContext::m_ib;
    std::unique_ptr<Shader> Sprite::SpriteContext::m_shader;
    std::unordered_map<std::string, std::weak_ptr<Sprite::SpriteContext>> Sprite::m_contextCache;

    Sprite::SpriteContext::SpriteContext(float width, float height)
        : m_width(width), m_height(height)
    {
        if (!m_ib) {
            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };
            m_ib = std::make_unique<IndexBuffer>(indices, 6);
        }

        if (!m_shader) {
            m_shader = std::make_unique<Shader>("resources/shaders/Texture.shader");
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

    void Sprite::InitContext(float width, float height) {
        std::stringstream name;
        name << width << "," << height;
        if (m_contextCache.find(name.str()) != m_contextCache.end())
            if (m_context = m_contextCache[name.str()].lock())
                return;

        m_context = std::make_shared<SpriteContext>(width, height);
        m_contextCache[name.str()] = m_context;
    }

	Sprite::Sprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture)
        : m_translation(x, y, 0), m_texture(texture)
    {
        InitContext(width, height);
    }

    Sprite::~Sprite() {
        std::stringstream name;
        name << m_context->m_width << "," << m_context->m_height;
        m_context = nullptr;

        if (!m_contextCache[name.str()].lock())
            m_contextCache.erase(name.str());
    }

    void Sprite::Draw(const glm::mat4& proj_view) {
        Renderer renderer;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
        glm::mat4 mvp = proj_view * model;

        m_texture->Bind();

        m_context->m_shader->Bind();
        m_context->m_shader->SetUniform1i("u_Texture", 0);
        m_context->m_shader->SetUniformMat4f("u_MVP", mvp);

        m_context->m_vb->Bind();
        renderer.Draw(*(m_context->m_va), *(m_context->m_ib), *(m_context->m_shader));
    }
}