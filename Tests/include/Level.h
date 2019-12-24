#pragma once

#include "Darnel.h"

namespace test {
    class Level : public darnel::Layer {
    public:
        Level(const std::string &name = "Level")
            : darnel::Layer(name)
        {}

        virtual ~Level() {}

        inline darnel::CameraLayer *GetCameraLayer() { return &m_CameraLayer; }
        inline darnel::EntityLayer *GetEntityLayer() { return &m_EntityLayer; }
        inline darnel::StaticEntityLayer *GetStaticEntityLayer() { return &m_StaticEntityLayer; }

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        virtual void OnUpdate() {
            m_CameraLayer.OnUpdate();
            m_EntityLayer.OnUpdate();
            m_StaticEntityLayer.OnUpdate();
        }

        virtual void OnEvent(darnel::Event &event) {
            m_CameraLayer.OnEvent(event);
            m_EntityLayer.OnEvent(event);
            m_StaticEntityLayer.OnEvent(event);
        }

    private:
        darnel::CameraLayer m_CameraLayer;
        darnel::EntityLayer m_EntityLayer;
        darnel::StaticEntityLayer m_StaticEntityLayer;
    };
}
