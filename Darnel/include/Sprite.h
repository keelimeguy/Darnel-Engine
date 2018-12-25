#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Texture.h"

namespace darnel {
    class Sprite {
    public:
        Sprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture)
            : m_translation(x, y, 0), m_texture(texture) {}

        virtual void Draw(const glm::mat4& proj_view) = 0;

    protected:
        glm::vec3 m_translation;
        std::shared_ptr<Texture> m_texture;
    };
}
