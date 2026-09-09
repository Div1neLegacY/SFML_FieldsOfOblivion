#pragma once

#include <SFML/Graphics/Text.hpp>

#ifndef HOT_RELOAD_EXPORT
    #ifdef _WIN32
        #define HOT_RELOAD_EXPORT __declspec(dllexport)
    #else
        #define HOT_RELOAD_EXPORT __attribute__((visibility("default")))
    #endif
#endif

extern "C" {
    HOT_RELOAD_EXPORT int hot_reload_get_num();
}