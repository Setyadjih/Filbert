#pragma once

#include "Filbert/Layer.h"

namespace Filbert
{
    class FILBERT_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        float m_Time = 0.0f;
    };
}

