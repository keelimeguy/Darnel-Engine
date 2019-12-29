#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Event.h"
#include "WindowEvent.h"
#include "Renderer.h"
#include "ImGuiLayer.h"

namespace darnel {
    class Application {
    public:
        Application(std::string name = "Darnel App",
                    unsigned int width = 1280,
                    unsigned int height = 720
                   );

        virtual ~Application();

        void Run();
        void OnEvent(Event &e, Window *window);
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        std::weak_ptr<Window> NewWindow(std::string name = "New Window",
                                        unsigned int width = 1280,
                                        unsigned int height = 720
                                       );
        std::weak_ptr<Window> NewChildWindow(Window *parent,
                                             std::string name = "New Window",
                                             unsigned int width = 1280,
                                             unsigned int height = 720
                                            );

        inline std::weak_ptr<Window> GetWindow() {
            Window *window = m_ActiveWindow;
            auto it = std::find_if(m_Windows.begin(), m_Windows.end(),
            [window](auto & wnd) { return wnd.get() == window; }
                                  );
            DARNEL_ASSERT(it != m_Windows.end(), "No active window");

            return *it;
        }

        inline static Application *Get() { return s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent &e, Window *window);
        bool OnWindowFocus(WindowFocusEvent &e, Window *window);

        std::vector<std::shared_ptr<Window>> m_Windows;
        Window *m_ActiveWindow;
        ImGuiLayer *m_ImGuiLayer;
        LayerStack m_LayerStack;
        bool m_Running = true;

        static Application *s_Instance;
    };

    Application *CreateApplication();
}
