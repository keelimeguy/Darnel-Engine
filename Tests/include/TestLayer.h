#pragma once

#include "Darnel.h"
#include "Test.h"
#include "TestCamera.h"
#include "TestClearColor.h"
#include "TestSprite.h"
#include "TestSpriteSheet.h"
#include "TestMultiWindow.h"

namespace test {
    class TestLayer : public darnel::ImGuiLayer {
    public:
        TestLayer()
            : m_CurrentTest(nullptr), m_TestMenu(m_CurrentTest)
        {
            m_CurrentTest = &m_TestMenu;
            m_TestMenu.RegisterTest<test::TestClearColor>("Clear Color");
            m_TestMenu.RegisterTest<test::TestSprite>("Sprites");
            m_TestMenu.RegisterTest<test::TestSpriteSheet>("SpriteSheet");
            m_TestMenu.RegisterTest<test::TestCamera>("Camera");
            m_TestMenu.RegisterTest<test::TestMultiWindow>("Multiple Windows");
        }

        void Render() override {
            if (m_CurrentTest) {
                m_CurrentTest->OnUpdate(0.0f);
                m_CurrentTest->OnRender();
                ImGui::Begin("Test");
                if (m_CurrentTest != &m_TestMenu && ImGui::Button("<-")) {
                    delete m_CurrentTest;
                    m_CurrentTest = &m_TestMenu;
                }
                m_CurrentTest->OnImGuiRender();
                ImGui::End();
            }
        }

    private:
        Test* m_CurrentTest;
        TestMenu m_TestMenu;
    };
}
