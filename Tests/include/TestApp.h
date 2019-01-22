#pragma once

#include "Darnel.h"
#include "TestLayer.h"

namespace test {
    class TestApp : public darnel::Application {
    public:
        TestApp()
            : darnel::Application("Darnel Test App")
        {
            PushOverlay(new TestLayer());
        }
    };
}

darnel::Application* darnel::CreateApplication() {
    return new test::TestApp();
}
