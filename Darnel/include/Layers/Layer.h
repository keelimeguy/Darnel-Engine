#pragma once

#include "Core.h"
#include "Event.h"

namespace darnel {
    class Layer {
    public:
        Layer(const std::string &name = "Layer") : m_Name(name) {}
        virtual ~Layer() {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}

        inline const std::string &GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}
