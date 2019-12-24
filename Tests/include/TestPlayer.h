#pragma once

#include "Test.h"

#include "PlayerCamera.h"

#include "Camera.h"
#include "Entity.h"
#include "Sprite.h"
#include "Event.h"
#include "KeyEvent.h"

namespace test {
    class Player;

    class TestPlayer : public Test {
    public:
        TestPlayer(int i = 0);

        void OnEvent(darnel::Event &e) override;
        void OnUpdate() override;
        void OnRender() override;
        void OnImGuiRender() override;

        static const int s_NumSettings;
        static const char *s_Settings[];

    private:
        bool m_fixPlayer = false;
        float m_x = 0.0f, m_y = 0.0f, m_z = 0.0f;

        std::shared_ptr<PlayerCamera> m_camera;
        std::shared_ptr<Player> m_player;
    };

    class Player : public darnel::Entity {
    public:
        Player(float x, float y, std::shared_ptr<darnel::Sprite> sprite)
            : darnel::Entity(x, y, sprite)
        {}

        virtual void OnUpdate() {
            float vel_x = 0.0f, vel_y = 0.0f;
            if (m_right) vel_x++;
            if (m_left) vel_x--;
            if (m_down) vel_y--;
            if (m_up) vel_y++;
            Move(vel_x, vel_y);
        }

        virtual void OnEvent(darnel::Event &e) {
            darnel::EventDispatcher dispatcher(e);
            if (dispatcher.Dispatch<darnel::KeyPressedEvent>(std::bind(&Player::OnKeyPress, this, std::placeholders::_1))) ;
            else if (dispatcher.Dispatch<darnel::KeyReleasedEvent>(std::bind(&Player::OnKeyRelease, this, std::placeholders::_1))) ;
        }

    private:
        bool OnKeyPress(darnel::KeyPressedEvent &e) {
            switch (e.GetKeyCode()) {
                case 262://GLFW_KEY_RIGHT:
                    m_right = 1; break;
                case 263://GLFW_KEY_LEFT:
                    m_left = 1; break;
                case 264://GLFW_KEY_DOWN:
                    m_down = 1; break;
                case 265://GLFW_KEY_UP:
                    m_up = 1; break;
            }
            return true;
        }

        bool OnKeyRelease(darnel::KeyReleasedEvent &e) {
            switch (e.GetKeyCode()) {
                case 262://GLFW_KEY_RIGHT:
                    m_right = 0; break;
                case 263://GLFW_KEY_LEFT:
                    m_left = 0; break;
                case 264://GLFW_KEY_DOWN:
                    m_down = 0; break;
                case 265://GLFW_KEY_UP:
                    m_up = 0; break;
            }
            return true;
        }

        bool m_left = false, m_right = false, m_down = false, m_up = false;
    };
}
