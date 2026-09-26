#pragma once

#include <filesystem>
#include <SFML/Graphics/Rect.hpp>


// #############################################################################
//                           Assets Constants
// #############################################################################

const std::filesystem::path SPRITE_ATLAS_MASTER = "assets/textures/TEXTURE_ATLAS_MASTER.png";
const std::filesystem::path SPRITE_ATLAS_SWEEP_ANIMATION = "assets/textures/hit_animations/swing01.png";
const std::filesystem::path SPRITE_ATLAS_WEAPON_BLAZE_BOOK_ANIMATION = "assets/textures/hit_animations_3/circle02.png";

// #############################################################################
//                           Assets Structs
// #############################################################################
enum SpriteID
{
	SPRITE_WHITE,
	SPRITE_DICE,
	// Player Sprites
	SPRITE_PLAYER,
	SPRITE_WEAPON_SWORD,
	SPRITE_WEAPON_BLAZE_BOOK,
	// Sprite Solids
	SPRITE_SOLID_01,
	SPRITE_SOLID_02,
	// Buttons
	SPRITE_BUTTON_PLAY,
	SPRITE_BUTTON_SAVE,
	// Tiles
	SPRITE_TILE_GRASS_01,
	// Projectiles
	SPRITE_BASIC_PROJECTILE,
	// Exp Orbs
	SPRITE_EXP_ORB_SMALL,
	// Count of sprite assets
	SPRITE_COUNT
};

struct Sprite
{
	sf::IntRect rectangle;
	std::filesystem::path file;
	// @todo Still need this frameCount?
	int frameCount = 1;
};

// #############################################################################
//                           Assets Functions
// #############################################################################
inline Sprite get_sprite(SpriteID spriteID)
{
	Sprite sprite = {};
	sprite.frameCount = 1;

	switch (spriteID)
	{
		case SPRITE_WHITE:
		{
			sprite.rectangle.position = {0, 0};
			sprite.rectangle.size = {1, 1};
			break;
		}

		case SPRITE_DICE:
		{
			sprite.rectangle.position = {16, 0};
			sprite.rectangle.size = {16, 16};
			break;
		}

		case SPRITE_EXP_ORB_SMALL:
		{
			sprite.rectangle.position = {0, 48};
			sprite.rectangle.size = {16, 16};
			sprite.file = SPRITE_ATLAS_MASTER;
			break;
		}

		case SPRITE_PLAYER:
		{
			sprite.rectangle.position = {112, 0};
			sprite.rectangle.size = {221, 20};
			sprite.file = SPRITE_ATLAS_MASTER;
			sprite.frameCount = 13;
			break;
		}

		case SPRITE_WEAPON_SWORD:
		{
			sprite.rectangle.position = {0, 0};
			sprite.rectangle.size = {704, 64};
			sprite.file = SPRITE_ATLAS_SWEEP_ANIMATION;
			sprite.frameCount = 11;
			break;
		}

		case SPRITE_WEAPON_BLAZE_BOOK:
		{
			sprite.rectangle.position = {0, 0};
			sprite.rectangle.size = {512, 64};
			sprite.file = SPRITE_ATLAS_WEAPON_BLAZE_BOOK_ANIMATION;
			sprite.frameCount = 8;
			break;
		}
		
		case SPRITE_SOLID_01:
		{
			sprite.rectangle.position = {0, 16};
			sprite.rectangle.size = {28, 18};
			sprite.file = SPRITE_ATLAS_MASTER;
			break;
		}

		case SPRITE_SOLID_02:
		{
			sprite.rectangle.position = {32, 16};
			sprite.rectangle.size = {16, 13};
			sprite.file = SPRITE_ATLAS_MASTER;
			break;
		}

		case SPRITE_BUTTON_PLAY:
		{
			sprite.rectangle.position = {80, 0};
			sprite.rectangle.size = {32, 16};
			sprite.file = SPRITE_ATLAS_MASTER;
			break;
		}

		case SPRITE_BUTTON_SAVE:
		{
			sprite.rectangle.position = {80, 16};
			sprite.rectangle.size = {32, 16};
			sprite.file = SPRITE_ATLAS_MASTER;
			break;
		}

		case SPRITE_TILE_GRASS_01:
		{
			sprite.rectangle.position = {112, 32};
			sprite.rectangle.size = {95, 95};
			sprite.file = SPRITE_ATLAS_MASTER;
			break;
		}

		// Atlas "projectiles"
		case SPRITE_BASIC_PROJECTILE:
		{
			sprite.rectangle.position = {35, 35};
			sprite.rectangle.size = {10, 10};
		}
	}

	return sprite;
}
