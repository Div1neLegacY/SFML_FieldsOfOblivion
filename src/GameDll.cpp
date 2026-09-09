#include "GameHotReload.hpp"

#include <iostream>

// Define macro if not already explicitly defined
#ifndef HOT_RELOAD_EXPORT
    #ifdef _WIN32
        #define HOT_RELOAD_EXPORT __declspec(dllexport)
    #else
        #define HOT_RELOAD_EXPORT __attribute__((visibility("default")))
    #endif
#endif

extern "C" {
    HOT_RELOAD_EXPORT int hot_reload_get_num()
    {
        return 32;
    }
}
