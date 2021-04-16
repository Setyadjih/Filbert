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

        void OnAttach();
        void OnDetach();
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);

        bool OnWindowResizedEvent(WindowResizeEvent& e);
    private:
        float m_Time = 0.0f;
    };
}

