#pragma once

#ifdef FB_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
    #ifdef FILBERT_BUILD_DLL
        #define FILBERT_API __declspec(dllexport)
    #else
        #define FILBERT_API __declspec(dllimport)
    #endif
#else
    #define FILBERT_API
#endif
#else
    #error Filbert is Windows only!
#endif

#ifdef FB_DEBUG
    #define HZ_ENABLE_ASSERTS
#endif

#if FB_ENABLE_ASSERTS
    #define FB_ASSERT(x, ...) { if (!(x)) { FB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
    #define FB_CORE_ASSERT(x, ...) { if (!(x)) { FB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
    #define FB_ASSERT(x, ...)
    #define FB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

// bind + placeholders works like functools.partial in python
#define FB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)