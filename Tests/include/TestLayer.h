#pragma once

#include "Darnel.h"
#include "Test.h"
#include "TestCamera.h"
#include "TestClearColor.h"
#include "TestSprite.h"
#include "TestSpriteSheet.h"
#include "TestPlayer.h"
#include "TestMultiWindow.h"
#include "TestLevel.h"

namespace test {
    class TestLayer : public darnel::Layer {
    public:
        TestLayer()
            : m_CurrentTest(nullptr), m_TestMenu(m_CurrentTest) {
            m_CurrentTest = &m_TestMenu;
            m_TestMenu.RegisterTest<test::TestClearColor>("Clear Color");
            m_TestMenu.RegisterTest<test::TestSprite>("Sprites");
            m_TestMenu.RegisterTest<test::TestPlayer>("Player");
            m_TestMenu.RegisterTest<test::TestSpriteSheet>("SpriteSheet");
            m_TestMenu.RegisterTest<test::TestCamera>("Camera");
            // m_TestMenu.RegisterTest<test::TestMultiWindow>("Multiple Windows");
            m_TestMenu.RegisterTest<test::TestLevel>("Level");
        }

        void OnUpdate() override {
            if (m_CurrentTest)
                m_CurrentTest->OnUpdate();
        }

        void OnEvent(darnel::Event &event) override {
            if (m_CurrentTest)
                m_CurrentTest->OnEvent(event);
        }

        void OnImGuiRender() override {
            if (m_CurrentTest) {
                m_CurrentTest->OnRender();
                if (m_CurrentTest != &m_TestMenu && ImGui::Button("<-")) {
                    delete m_CurrentTest;
                    m_CurrentTest = &m_TestMenu;
                }
                m_CurrentTest->OnImGuiRender();
            }
        }

    private:
        Test *m_CurrentTest;
        TestMenu m_TestMenu;
    };
}
