#pragma once

#include "Filbert/Layer.h"

#include "Filbert/Events/ApplicationEvent.h"
#include "Filbert/Events/KeyEvent.h"
#include "Filbert/Events/MouseEvent.h"


namespace Filbert
{
    class FILBERT_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}

