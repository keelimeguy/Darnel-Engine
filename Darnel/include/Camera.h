#pragma once

#include "Core.h"
#include "Event.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace darnel {
    class Camera;

    static std::shared_ptr<Camera> MakeOrthographicCamera(
        float left = 0.0f, float right = 640.0f,
        float bottom = 0.0f, float top = 480.0f,
        float near = -1.0f, float far = 1.0f) {
        return std::make_shared<Camera>(glm::ortho(left, right, bottom, top, near, far));
    }

    class Camera {
    public:
        Camera(glm::mat4 proj)
            : m_proj(proj), m_view(glm::mat4(1.0f))
        {}

        void Move(float dx, float dy, float dz = 0.0f) {
            m_view = glm::translate(m_view, glm::vec3(-dx, -dy, -dz));
        }

        void MoveTo(float x, float y, float z) {
            m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-x, -y, -z));
        }

        virtual void OnUpdate() {}
        virtual void OnEvent(Event &e) {}

        glm::mat4 GetProjView() { return m_proj * m_view; }

    private:
        glm::mat4 m_proj, m_view;
    };

}
