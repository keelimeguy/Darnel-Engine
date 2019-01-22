#pragma once

#include "Darnel.h"

class TestApp : public darnel::Application {
public:
    TestApp() {
        // PushLayer();
        PushOverlay(new darnel::ImGuiLayer());
    }
};

darnel::Application* darnel::CreateApplication() {
    return new TestApp();
}
