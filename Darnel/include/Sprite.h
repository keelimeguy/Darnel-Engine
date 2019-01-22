#pragma once

#include "Core.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace darnel {
    class Sprite {
    public:
        static std::shared_ptr<Sprite> Create(float x, float y, float width, float height, std::shared_ptr<Texture> texture);

        Sprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture)
            : m_translation(x, y, 0), m_texture(texture) {}
        virtual ~Sprite() {}

        virtual void Draw(const glm::mat4& proj_view) = 0;

    protected:
        glm::vec3 m_translation;
        std::shared_ptr<Texture> m_texture;
    };
}
