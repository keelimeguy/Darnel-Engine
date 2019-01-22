#pragma once

#include "Core.h"
#include "Event.h"
#include "WindowEvent.h"

namespace darnel {
    class Window {
    public:
        static std::shared_ptr<Window> Create(std::string name, unsigned int width, unsigned int height);

        Window(std::string name, unsigned int width, unsigned int height)
            : m_Name(name), m_Width(width), m_Height(height)
        {}

        virtual ~Window() {
            for (auto child : m_Children) child->Close();
        }

        virtual void OnUpdate() = 0;
        virtual void Focus() = 0;
        virtual void Close() = 0;

        virtual std::string GetName() const { return m_Name; }
        virtual unsigned int GetWidth() const { return m_Width; }
        virtual unsigned int GetHeight() const { return m_Height; }
        virtual unsigned int GetXPos() const { return m_XPos; }
        virtual unsigned int GetYPos() const { return m_YPos; }

        virtual void AddEventCallback(const std::function<void(Event&)>& callback) {
            m_EventCallbacks.push_back(callback);
        }

        virtual std::shared_ptr<Window> MakeChild(std::string name, unsigned int width, unsigned int height) {
            auto child = Create(name, width, height);
            m_Children.push_back(child.get());

            child->AddEventCallback(std::bind(&Window::OnChildEvent, this, std::placeholders::_1, child.get()));
            return child;
        }

    protected:
        std::string m_Name;
        int m_Width, m_Height, m_XPos, m_YPos;
        std::vector<std::function<void(Event&)>> m_EventCallbacks;
        std::vector<Window*> m_Children;

        virtual void Broadcast(Event& e) {
            for (auto callback : m_EventCallbacks)
                callback(e);
        }

        virtual void OnChildEvent(Event& e, Window* window) {
            EventDispatcher dispatcher(e);
            dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Window::OnChildClose, this, std::placeholders::_1, window));
        }

        virtual bool OnChildClose(WindowCloseEvent& e, Window* window) {
            auto it = std::find_if(m_Children.begin(), m_Children.end(),
                [window](auto& wnd) { return wnd == window; }
            );
            DARNEL_ASSERT(it != m_Children.end(), "Unknown child");
            m_Children.erase(it);
            return true;
        }
    };
}
