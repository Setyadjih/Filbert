#include "fbpch.h"
#include "Log.h"

namespace Filbert
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
    
    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("FILBERT");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stderr_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}