#pragma once

#ifdef FB_PLATFORM_WINDOWS

extern Filbert::Application* Filbert::CreateApplication();

int main(int argc, char** argv)
{
    Filbert::Log::Init();

    FB_CORE_WARN("InitializedLog!");

    auto app = Filbert::CreateApplication();
    app->Run();
    delete app;
}

#endif