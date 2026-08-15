#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include "Assets.hpp"
const sf::String GAME_TITLE = "Fields of Oblivion";
const std::filesystem::path GAME_TITLE_FONT_PATH = "assets/fonts/Star Crush.ttf";
const sf::Font GAME_TITLE_FONT = sf::Font(GAME_TITLE_FONT_PATH);
const sf::Texture SPRITE_BUTTON_PLAY_TEXTURE = sf::Texture(SPRITE_ATLAS_MASTER, false, get_sprite(SPRITE_BUTTON_PLAY).rectangle);
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const sf::Color BUTTON_HOVER_COLOR(50, 170, 90);   // Soft emerald green