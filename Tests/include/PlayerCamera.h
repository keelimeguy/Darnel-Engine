#pragma once

#include "Camera.h"

namespace test {
    class PlayerCamera : public darnel::Camera {
    public:
        PlayerCamera(float left = 0.0f, float right = 640.0f,
                     float bottom = 0.0f, float top = 480.0f,
                     float near = -1.0f, float far = 1.0f
                    )
            : darnel::Camera(glm::ortho(left, right, bottom, top, near, far)), m_speed(2.0f)
        {}

        void OnUpdate() override {
            float vel_x = 0.0f, vel_y = 0.0f;
            if (m_right) vel_x += m_speed;
            if (m_left) vel_x -= m_speed;
            if (m_down) vel_y -= m_speed;
            if (m_up) vel_y += m_speed;
            Move(vel_x, vel_y);
        }

        void OnEvent(darnel::Event &e) override {
            darnel::EventDispatcher dispatcher(e);
            if (dispatcher.Dispatch<darnel::KeyPressedEvent>(std::bind(&PlayerCamera::OnKeyPress, this, std::placeholders::_1))) ;
            else if (dispatcher.Dispatch<darnel::KeyReleasedEvent>(std::bind(&PlayerCamera::OnKeyRelease, this,
                     std::placeholders::_1))) ;
        }

    private:
        bool OnKeyPress(darnel::KeyPressedEvent &e) {
            switch (e.GetKeyCode()) {
                case 262://GLFW_KEY_RIGHT:
                    m_right = true; break;
                case 263://GLFW_KEY_LEFT:
                    m_left = true; break;
                case 264://GLFW_KEY_DOWN:
                    m_down = true; break;
                case 265://GLFW_KEY_UP:
                    m_up = true; break;
                case 340://GLFW_KEY_LSHIFT:
                    m_speed *= 2.0f; break;
            }
            return true;
        }

        bool OnKeyRelease(darnel::KeyReleasedEvent &e) {
            switch (e.GetKeyCode()) {
                case 262://GLFW_KEY_RIGHT:
                    m_right = false; break;
                case 263://GLFW_KEY_LEFT:
                    m_left = false; break;
                case 264://GLFW_KEY_DOWN:
                    m_down = false; break;
                case 265://GLFW_KEY_UP:
                    m_up = false; break;
                case 340://GLFW_KEY_LSHIFT:
                    m_speed /= 2.0f; break;
            }
            return true;
        }

        bool m_left = false, m_right = false, m_down = false, m_up = false;
        float m_speed;
    };
}
