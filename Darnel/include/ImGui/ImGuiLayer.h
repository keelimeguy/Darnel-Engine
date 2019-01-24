#pragma once

#include "Layer.h"
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"

#include <imgui.h>

namespace darnel {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() : Layer("ImGuiLayer") {}

        virtual void OnAttach() override;
        virtual void OnEvent(Event& event) override;
        virtual void OnUpdate() override;

        virtual void Render();

    private:
        float m_Time = 0.0f;

        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
    };
}
