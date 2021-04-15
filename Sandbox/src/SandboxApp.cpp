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
        FB_INFO("ExampleLayer::Update");
    }

    void OnEvent(Filbert::Event& event) override
    {
        FB_TRACE("{0}", event);
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