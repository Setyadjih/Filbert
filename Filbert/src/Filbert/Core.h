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