#include <Filbert.h>

class Sandbox : public Filbert::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }

};

Filbert::Application* Filbert::CreateApplication()
{
    return new Sandbox();
}