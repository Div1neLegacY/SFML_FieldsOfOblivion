#pragma once

#include "Main.hpp"
#include "HealthBar.hpp"
#include "AnimatedSprite.hpp"

class Player
{
public:
	Player();
	virtual ~Player();
//private:
    AnimatedSprite* sprite;
    sf::View* camera;
    HealthBar* healthBar;
};