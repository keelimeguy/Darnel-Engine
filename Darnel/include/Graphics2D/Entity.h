#pragma once

#include "Core.h"
#include "Event.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace darnel {
    class Entity {
    public:
        Entity(float x, float y, std::shared_ptr<Sprite> sprite)
            : m_translation(x, y, 0), m_Sprite(sprite) {}

        virtual ~Entity() {}

        virtual void OnEvent(Event &e) {}
        virtual void OnUpdate() {}

        virtual void Move(float dx, float dy, float dz = 0.0f) {
            m_translation += glm::vec3(dx, dy, dz);
        }

        virtual void MoveTo(float x, float y, float z) {
            m_translation = glm::vec3(x, y, z);
        }

        virtual void Draw(const glm::mat4 &proj_view) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
            glm::mat4 mvp = proj_view * model;
            m_Sprite->Draw(mvp);
        };

    protected:
        glm::vec3 m_translation;
        std::shared_ptr<Sprite> m_Sprite;
    };
}
