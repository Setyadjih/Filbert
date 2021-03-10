#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Filbert
{
    class FILBERT_API Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };

}

// Core Log macros
#define FB_CORE_TRACE(...)   ::Filbert::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FB_CORE_INFO(...)    ::Filbert::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FB_CORE_WARN(...)    ::Filbert::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FB_CORE_ERROR(...)   ::Filbert::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FB_CORE_FATAL(...)   ::Filbert::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define FB_TRACE(...)        ::Filbert::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FB_INFO(...)         ::Filbert::Log::GetClientLogger()->info(__VA_ARGS__)
#define FB_WARN(...)         ::Filbert::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FB_ERROR(...)        ::Filbert::Log::GetClientLogger()->error(__VA_ARGS__)
#define FB_FATAL(...)        ::Filbert::Log::GetClientLogger()->fatal(__VA_ARGS__)
