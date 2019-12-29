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

        void Begin();
        void End();

        virtual void OnAttach() override;
        virtual void OnDetach() override;

    private:
        float m_Time = 0.0f;
    };
}
