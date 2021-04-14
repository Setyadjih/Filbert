#pragma once

#ifdef FB_PLATFORM_WINDOWS
    #ifdef FILBERT_BUILD_DLL
        #define FILBERT_API __declspec(dllexport)
    #else
        #define FILBERT_API __declspec(dllimport)
    #endif
#else
    #error Filbert is Windows only!
#endif

#ifdef FB_ENABLE_ASSERTS
    #define FB_ASSERT(x, ...) { if (!(x)) { FB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
    #define FB_CORE_ASSERT(x, ...) { if (!(x)) { FB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
    #define FB_ASSERT(x, ...)
    #define FB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)