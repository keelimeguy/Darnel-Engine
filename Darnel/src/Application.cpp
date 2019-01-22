#include "Application.h"

namespace darnel {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        DARNEL_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_ActiveWindow = Window::Create();
        m_ActiveWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1, m_ActiveWindow));

        m_Windows.push_back(std::unique_ptr<Window>(m_ActiveWindow));
    }

    Application::~Application() {
        m_Windows.clear();
        Renderer::Terminate();
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e, Window* window) {
        std::cout << "[" << window->GetName() << "] " << e.ToString() << std::endl << std::flush;

        EventDispatcher dispatcher(e);
        if (dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1, window))) ;
        else if (dispatcher.Dispatch<WindowFocusEvent>(std::bind(&Application::OnWindowFocus, this, std::placeholders::_1, window))) ;
        else {
            for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
                (*--it)->OnEvent(e);
                if (e.IsHandled())
                    break;
            }
        }
    }

    void Application::Run() {
        while (m_Running) {
            Renderer::Clear();

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            // for (Window* window : m_Windows)
                // window->OnUpdate();

            m_ActiveWindow->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e, Window* window) {
        // We need a context still active during termination,
        // so don't delete the window if it is the last one
        if (m_Windows.size() == 1 && m_Windows[0].get() == window)
            m_Running = false;

        else {
            m_Windows.erase(std::find_if(m_Windows.begin(), m_Windows.end(),
                [window](auto& wnd) { return wnd.get() == window; }
            ));
            m_ActiveWindow = m_Windows.back().get();
        }

        return true;
    }

    bool Application::OnWindowFocus(WindowFocusEvent& e, Window* window) {
        m_ActiveWindow = window;
        // window->MakeActiveContext();
        return true;
    }
}
