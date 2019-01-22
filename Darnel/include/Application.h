#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Event.h"
#include "WindowEvent.h"

// TODO: separate into own Renderer.h
#include "OpenGL3/OpenGL3Renderer.h"

namespace darnel {
    class Application {
    public:
        inline static Application& Get() { return *s_Instance; }

        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e, Window* window);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_ActiveWindow; }

    private:
        static Application* s_Instance;

        std::vector<std::unique_ptr<Window>> m_Windows;
        LayerStack m_LayerStack;
        Window* m_ActiveWindow;
        bool m_Running = true;

        bool OnWindowClose(WindowCloseEvent& e, Window* window);
        bool OnWindowFocus(WindowFocusEvent& e, Window* window);
    };

    Application* CreateApplication();
}
