#pragma once

#include "Core.h"
#include "Entity.h"
#include "Event.h"
#include "Layer.h"
#include "Camera.h"

namespace darnel {
    class EntityLayer : public Layer {
    public:
        EntityLayer(const std::string &name = "EntityLayer");
        virtual ~EntityLayer();

        virtual void OnUpdate();
        virtual void OnEvent(darnel::Event &event);

        void PushEntity(std::shared_ptr<Entity> e);
        void PopEntity(std::shared_ptr<Entity> e);

        void SetCamera(std::shared_ptr<Camera> camera) {
            m_Camera = camera;
        }

    protected:
        std::vector<std::shared_ptr<Entity>> m_Entities;
        std::shared_ptr<Camera> m_Camera;
    };
}
