#pragma once

#include <SFML/Graphics/Text.hpp>

#if defined(_WIN32)
#define HOT_RELOAD_EXPORT __declspec(dllexport)
#else
#define HOT_RELOAD_EXPORT
#endif

extern "C" {
    HOT_RELOAD_EXPORT void hot_reload_set_title(sf::Text& text, const char* newTitle);
}
