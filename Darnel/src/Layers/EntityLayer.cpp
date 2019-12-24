#include "EntityLayer.h"

namespace darnel {
    EntityLayer::EntityLayer(const std::string &name)
        : Layer(name) {}

    EntityLayer::~EntityLayer() {
        m_Entities.clear();
    }

    void EntityLayer::OnUpdate() {
        for (auto &e : m_Entities)
            e->OnUpdate();

        auto proj_view = m_Camera->GetProjView();
        for (auto &e : m_Entities)
            e->Draw(proj_view);
    }

    void EntityLayer::OnEvent(Event &event) {
        for (auto &e : m_Entities)
            e->OnEvent(event);
    }

    void EntityLayer::PushEntity(std::shared_ptr<Entity> e) {
        m_Entities.emplace_back(e);
    }

    void EntityLayer::PopEntity(std::shared_ptr<Entity> e) {
        auto it = std::find(m_Entities.begin(), m_Entities.end(), e);
        if (it != m_Entities.end())
            m_Entities.erase(it);
    }
}
