#pragma once

#include "Darnel.h"

namespace test {
    class Test {
    public:
        Test(int i = 0) {}
        virtual ~Test() {}

        virtual void OnEvent(darnel::Event &e) {}
        virtual void OnUpdate() {}
        virtual void OnRender() {}

        virtual void OnImGuiRender() {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }

        static const int s_NumSettings;
        static const char *s_Settings[];
    };

    class TestMenu : public Test {
    private:

        class TestOption {
        public:
            TestOption(std::string name, const int numSettings, const char **settings, std::function<Test*(int)> callback)
                : m_choice(0), m_Name(name), m_NumSettings(numSettings), m_Settings(settings), m_Callback(callback) {}
            std::string Name() { return m_Name; }
            const int NumSettings() { return m_NumSettings; }
            const char **Settings() { return m_Settings; }
            std::function<Test*(int)> Callback() { return m_Callback; }
            int m_choice;

        private:
            std::string m_Name;
            const int m_NumSettings;
            const char **m_Settings;
            std::function<Test*(int)> m_Callback;
        };

    public:
        TestMenu(Test *&currentTest);

        void OnRender() override;
        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string &name) {
            std::cout << "Registering test " << name << std::endl;
            if (T::s_NumSettings)
                m_Tests.push_back(std::make_shared<TestOption>(name, T::s_NumSettings, T::s_Settings, [](int i) {return new T(i);}));
            else
                m_Tests.push_back(std::make_shared<TestOption>(name, T::s_NumSettings, T::s_Settings, [](int i) {return new T();}));
        }

    private:
        Test *&m_CurrentTest;
        std::vector<std::shared_ptr<TestOption>> m_Tests;
    };
}
