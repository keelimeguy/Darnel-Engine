#pragma once

#include "Core.h"
#include "Entity.h"
#include "Event.h"
#include "Layer.h"
#include "EntityLayer.h"
#include "Camera.h"

namespace darnel {
    class StaticEntityLayer : public EntityLayer {
    public:
        StaticEntityLayer(const std::string &name = "StaticEntityLayer") : EntityLayer(name) {}
        virtual ~StaticEntityLayer() {}

        virtual void OnUpdate() {
            for (auto &e : m_Entities)
                e->OnUpdate();

            auto proj = m_Camera->GetProj();
            for (auto &e : m_Entities)
                e->Draw(proj);
        }
    };
}
