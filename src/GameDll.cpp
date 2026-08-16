#include "GameHotReload.hpp"

#include <iostream>

extern "C" {
    HOT_RELOAD_EXPORT void hot_reload_set_title(sf::Text& text, const char* newTitle)
    {
        text.setString(sf::String(newTitle));
        std::cout << "Hot reload title set to: " << newTitle << std::endl;
    }
}
