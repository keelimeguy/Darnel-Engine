#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <unordered_map>

#include "Sprite.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "OpenGL3Shader.h"

namespace darnel {
    class OpenGL3Sprite : public Sprite {
    public:
        OpenGL3Sprite(float width, float height, std::shared_ptr<Texture> texture);
        ~OpenGL3Sprite();

        void Draw(const glm::mat4& mvp) override;

        class SpriteContext {
        public:
            static std::unique_ptr<IndexBuffer> s_ib;
            static std::unique_ptr<OpenGL3Shader> s_shader;

            SpriteContext(float width, float height);

            float m_width, m_height;
            std::unique_ptr<VertexArray> m_va;
            std::unique_ptr<VertexBuffer> m_vb;
        };

    private:
        void InitContext(float width, float height);

        static std::unordered_map<std::string, std::weak_ptr<SpriteContext>> s_contextCache;

        std::shared_ptr<SpriteContext> m_context;
    };
}
