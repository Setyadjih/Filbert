#include <Filbert.h>

class ExampleLayer : public Filbert::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {

        if (Filbert::Input::IsKeyPressed(FB_KEY_TAB)) { FB_TRACE("Tab is pressed!"); }
    }

    void OnEvent(Filbert::Event& event) override
    {
        if (event.GetEventType() == Filbert::EventType::KeyPressed)
        {
            Filbert::KeyPressedEvent& e = (Filbert::KeyPressedEvent&) event;
            FB_TRACE("{0}", (char) e.GetKeyCode());
        }
    }
};

class Sandbox : public Filbert::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Filbert::ImGuiLayer());
    } 

    ~Sandbox()
    {
    }

};

Filbert::Application* Filbert::CreateApplication()
{
    return new Sandbox();
}