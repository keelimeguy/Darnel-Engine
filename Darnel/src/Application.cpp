#include "Application.h"
#include "Sprite.h"

namespace darnel {
    Application *Application::s_Instance = nullptr;

    Application::Application(std::string name, unsigned int width, unsigned int height) {
        DARNEL_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Windows.push_back(Window::Create(name, width, height));
        m_ActiveWindow = m_Windows.back().get();
        m_ActiveWindow->AddEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1, m_ActiveWindow));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
        Sprite::SpriteContext::s_ib = nullptr;
        Sprite::SpriteContext::s_shader = nullptr;
        Renderer::Get()->Terminate(&m_Windows);
    }

    std::weak_ptr<Window> Application::NewWindow(std::string name, unsigned int width, unsigned int height) {
        m_Windows.push_back(Window::Create(name, width, height));
        auto window = m_Windows.back();
        window->AddEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1, window.get()));

        std::cout << "[" << name << "] " << "Created" << std::endl << std::flush;

        m_ActiveWindow->Focus();

        return window;
    }

    std::weak_ptr<Window> Application::NewChildWindow(Window *parent, std::string name, unsigned int width,
            unsigned int height) {
        m_Windows.push_back(parent->MakeChild(name, width, height));
        auto window = m_Windows.back();
        window->AddEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1, window.get()));

        std::cout << "[" << name << "] " << "Created" << std::endl << std::flush;

        m_ActiveWindow->Focus();

        return window;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event &e, Window *window) {
        std::cout << "[" << window->GetName() << "] " << e.ToString() << std::endl << std::flush;

        EventDispatcher dispatcher(e);
        if (dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1,
                window))) ;
        else if (dispatcher.Dispatch<WindowFocusEvent>(std::bind(&Application::OnWindowFocus, this, std::placeholders::_1,
                 window))) ;
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
            Window::PollEvents();

            Renderer::Get()->Clear();

            for (Layer *layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer *layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            for (auto &window : m_Windows)
                window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e, Window *window) {
        // We need a context still active during termination,
        // so don't delete the window if it is the last one
        if (m_Windows.size() == 1) {
            DARNEL_ASSERT(m_Windows[0].get() == window, "Closing unknown window");
            m_Running = false;

        } else {
            if (window == m_ActiveWindow) {
                m_ActiveWindow = nullptr;
            }

            auto it = std::find_if(m_Windows.begin(), m_Windows.end(),
            [window](auto & wnd) { return wnd.get() == window; }
                                  );
            DARNEL_ASSERT(it != m_Windows.end(), "Closing unknown window");
            DARNEL_ASSERT(it->get() == window, "Found wrong window");

            auto wnd = *it; // Prevents immediate deletion of child windows
            m_Windows.erase(it);

            if (!m_ActiveWindow) m_ActiveWindow = m_Windows.back().get();
        }

        return true;
    }

    bool Application::OnWindowFocus(WindowFocusEvent &e, Window *window) {
        auto it = std::find_if(m_Windows.begin(), m_Windows.end(),
        [window](auto & wnd) { return wnd.get() == window; }
                              );
        DARNEL_ASSERT(it != m_Windows.end(), "Set focus on unknown window");

        m_ActiveWindow = it->get();
        return true;
    }
}
