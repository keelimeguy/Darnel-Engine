#pragma once

#include "Core.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace darnel {
    class Sprite {
    public:
        static std::shared_ptr<Sprite> Create(float width, float height, std::shared_ptr<Texture> texture);

        Sprite(float width, float height, std::shared_ptr<Texture> texture);
        ~Sprite();

        void Draw(const glm::mat4 &mvp);

        class SpriteContext {
        public:
            static std::shared_ptr<IndexBuffer> s_ib;
            static std::shared_ptr<Shader> s_shader;

            SpriteContext(float width, float height);

            float m_width, m_height;
            std::shared_ptr<VertexArray> m_va;
            std::shared_ptr<VertexBuffer> m_vb;
        };

    protected:
        std::shared_ptr<Texture> m_texture;

    private:
        void InitContext(float width, float height);

        static std::unordered_map<std::string, std::weak_ptr<SpriteContext>> s_contextCache;

        std::shared_ptr<SpriteContext> m_context;
    };
}
