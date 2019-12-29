#pragma once

#include "Core.h"
#include "Event.h"
#include "Layer.h"
#include "Camera.h"

namespace darnel {
    class CameraLayer : public Layer {
    public:
        CameraLayer(const std::string &name = "Camera Layer") : Layer(name) {}
        virtual ~CameraLayer() {}

        void SetCamera(std::shared_ptr<Camera> camera) { m_Camera = camera; }

        virtual void OnUpdate() { m_Camera->OnUpdate(); }
        virtual void OnEvent(darnel::Event &event) { m_Camera->OnEvent(event); }

    protected:
        std::shared_ptr<Camera> m_Camera;
    };
}
