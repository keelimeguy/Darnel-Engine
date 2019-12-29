#include "Sprite.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include <sstream>

namespace darnel {
    std::shared_ptr<IndexBuffer> Sprite::SpriteContext::s_ib;
    std::shared_ptr<Shader> Sprite::SpriteContext::s_shader;
    std::unordered_map<std::string, std::weak_ptr<Sprite::SpriteContext>> Sprite::s_contextCache;

    std::shared_ptr<Sprite> Sprite::Create(float width, float height, std::shared_ptr<Texture> texture) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: DARNEL_ASSERT(false, "None is not a valid RendererAPI."); return nullptr;
            case RendererAPI::API::OpenGL3: return std::shared_ptr<Sprite>(new Sprite(width, height, texture));
        }

        DARNEL_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

    Sprite::SpriteContext::SpriteContext(float width, float height)
        : m_width(width), m_height(height) {
        if (!s_ib) {
            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };
            s_ib = IndexBuffer::Create(indices, 6);
        }

        if (!s_shader) {
            /** Supporting three ways of inputting shader **/

            /** Combined file **/
            s_shader = Shader::Create("resources/shaders/Texture.shader");

            /** Split files **/
            // s_shader = Shader::Create("resources/shaders/Texture_A.shader", "resources/shaders/Texture_B.shader");

            /** Hard-coded **/
            // ShaderProgramSource shaderSrc = {
            //     // Vertex Shader
            //     R"(
            //         #version 330 core

            //         layout(location = 0) in vec4 position;
            //         layout(location = 1) in vec2 texCoord;

            //         out vec2 v_TexCoord;

            //         uniform mat4 u_MVP;

            //         void main() {
            //             gl_Position = u_MVP * position;
            //             v_TexCoord = texCoord;
            //         };
            //     )",

            //     // Fragment Shader
            //     R"(
            //         #version 330 core

            //         layout(location = 0) out vec4 color;

            //         in vec2 v_TexCoord;

            //         uniform sampler2D u_Texture;

            //         void main() {
            //             vec4 texColor = texture(u_Texture, v_TexCoord);
            //             color = texColor;
            //         };
            //     )"
            // };

            // s_shader = Shader::Create(shaderSrc);
        }

        auto layout = VertexBufferLayout::Create();
        layout->Push("position", ShaderDataType::Float, 2);
        layout->Push("texCoord", ShaderDataType::Float, 2);

        float positions[] = {
            0.0f, 0.0f, 0.0f, 0.0f,    // 0
            width, 0.0f, 1.0f, 0.0f,   // 1
            width, height, 1.0f, 1.0f, // 2
            0.0f, height, 0.0f, 1.0f,  // 3
        };

        m_vb = VertexBuffer::Create(positions, (unsigned int) sizeof(positions));

        m_va = VertexArray::Create();
        m_va->AddBuffer(*m_vb, *layout);
    }

    void Sprite::InitContext(float width, float height) {
        std::stringstream name;
        name << width << "," << height;
        if (s_contextCache.find(name.str()) != s_contextCache.end())
            if (m_context = s_contextCache[name.str()].lock())
                return;

        m_context = std::make_shared<SpriteContext>(width, height);
        s_contextCache[name.str()] = m_context;
    }

    Sprite::Sprite(float width, float height, std::shared_ptr<Texture> texture)
        : m_texture(texture) {

        InitContext(width, height);
    }

    Sprite::~Sprite() {
        std::stringstream name;
        name << m_context->m_width << "," << m_context->m_height;
        m_context = nullptr;

        if (!s_contextCache[name.str()].lock())
            s_contextCache.erase(name.str());
    }

    void Sprite::Draw(const glm::mat4 &mvp) {
        m_texture->Bind();

        m_context->s_shader->Bind();
        m_context->s_shader->SetUniform1i("u_Texture", 0);
        m_context->s_shader->SetUniformMat4f("u_MVP", mvp);

        m_context->m_vb->Bind();
        Renderer::Get()->Submit(*(m_context->m_va), *(m_context->s_ib), *(m_context->s_shader));
    }
}
