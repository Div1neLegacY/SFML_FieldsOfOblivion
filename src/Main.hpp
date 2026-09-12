#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "AnimatedSprite.hpp"

const sf::String GAME_TITLE = "Fields of Oblivion";
const std::filesystem::path GAME_TITLE_FONT_PATH = "assets/fonts/Star Crush.ttf";
const sf::Font GAME_TITLE_FONT = sf::Font(GAME_TITLE_FONT_PATH);

/**
 * Sprite Constants
 */
const sf::Texture SPRITE_BUTTON_PLAY_TEXTURE   = sf::Texture(get_sprite(SPRITE_BUTTON_PLAY).file, false, get_sprite(SPRITE_BUTTON_PLAY).rectangle);
const sf::Texture SPRITE_PLAYER_TEXTURE        = sf::Texture(get_sprite(SPRITE_PLAYER).file, false, get_sprite(SPRITE_PLAYER).rectangle);
const sf::Texture SPRITE_PLAYER_ATTACK_TEXTURE = sf::Texture(get_sprite(SPRITE_PLAYER_ATTACK).file, false, get_sprite(SPRITE_PLAYER_ATTACK).rectangle);
const sf::Texture SPRITE_TILE_GRASS_01_TEXTURE = sf::Texture(get_sprite(SPRITE_TILE_GRASS_01).file, false, get_sprite(SPRITE_TILE_GRASS_01).rectangle);
const sf::Texture SPRITE_ENEMY_TEXTURE         = sf::Texture(get_sprite(SPRITE_SOLID_01).file, false, get_sprite(SPRITE_SOLID_01).rectangle);


const sf::Color BUTTON_HOVER_COLOR(50, 170, 90);   // Soft emerald green

// Define the global values in exactly one source file
const int GLOBAL_SPRITE_FRAME_WIDTH = 17;
const int GLOBAL_SPRITE_FRAME_HEIGHT = 20;

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const sf::Vector2f WINDOW_CENTER = sf::Vector2f{1280 / 2, 720 / 2};
constexpr int TILE_SIZE = 95;
const sf::Vector2f BACKGROUND_TILE_SCALE{2, 2};
// Window is around 7x4 tiles, but we use an extra padding of 1+ tile to accommodate
// for the wrap-around mechanics of an infinite looping background. For a 1+ tile
// padding, this will wrap the entire background in an additional layer giving us
// +2x in both x and y directions.
const unsigned int BEYOND_SCREEN_TILE_PADDING = 1;
const unsigned int NUM_OF_BACKGROUND_TILE_COLUMNS = 7 + (2 * BEYOND_SCREEN_TILE_PADDING);
const unsigned int NUM_OF_BACKGROUND_TILE_ROWS = 4 + (2 * BEYOND_SCREEN_TILE_PADDING);

/**
 * Player Constants
 */
const unsigned int MAX_HEALTH = 100;
const unsigned int HIT_DAMAGE = 10;
const float INVINCIBILITY_DURATION = 0.2f; // Invincibility duration in seconds after taking damage
const int CHARACTER_SCALE = 2;
const float ATTACK_COOLDOWN = 1.0f; // Cooldown duration in seconds between attacks


/**
 * Keybinds (KB)
 */
// Pause / Unpause
const auto KB_TOGGLE_PAUSE = sf::Keyboard::Key::Escape;
// Movements
const auto KB_MOVE_UP = sf::Keyboard::Key::W;
const auto KB_MOVE_DOWN = sf::Keyboard::Key::S;
const auto KB_MOVE_LEFT = sf::Keyboard::Key::A;
const auto KB_MOVE_RIGHT = sf::Keyboard::Key::D;


/**
 * Animation Sprites Settings
 */
// Player
const AnimationSpriteSettings DEFAULT_PLAYER_ANIMATION_SETTINGS = {
    .totalFrames = get_sprite(SPRITE_PLAYER).frameCount,
    .frameRect = sf::IntRect({0, 0}, {17, 20}),
};

// Player Attack
const AnimationSpriteSettings DEFAULT_PLAYER_ATTACK_ANIMATION_SETTINGS = {
    .totalFrames = get_sprite(SPRITE_PLAYER_ATTACK).frameCount,
    .frameRect = sf::IntRect({0, 0}, {64, 64}),
    .animationCooldownDuration = ATTACK_COOLDOWN,
    .initialSpriteBlank = true
};