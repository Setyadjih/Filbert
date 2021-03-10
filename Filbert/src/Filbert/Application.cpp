#include "Application.h"

#include "Filbert/Events/ApplicationEvent.h"
#include "Filbert/Log.h"

namespace Filbert
{
    Application::Application()
    {}

    Application::~Application()
    {}
    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        FB_TRACE(e);

        while (true);
    }
}
