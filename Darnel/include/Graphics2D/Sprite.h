#pragma once

#include "Core.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace darnel {
    class Sprite {
    public:
        static std::shared_ptr<Sprite> Create(float width, float height, std::shared_ptr<Texture> texture);

        Sprite(float width, float height, std::shared_ptr<Texture> texture)
            : m_texture(texture) {}
        virtual ~Sprite() {}

        virtual void Draw(const glm::mat4 &mvp) = 0;

    protected:
        std::shared_ptr<Texture> m_texture;
    };
}
