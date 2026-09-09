#pragma once

#include "Main.hpp"
#include "HealthBar.hpp"
#include "AnimatedSprite.hpp"

class Player
{
public:
	Player();
	virtual ~Player();
    void update(float dt);
//private:
    AnimatedSprite* sprite;
    sf::View* camera;
    //HealthBar* healthBar;
    std::unique_ptr<AnimatedSprite> attackAnimationSprite;
private:
    // Timer to track the cooldown period between attacks
    float attackTimer = 0.0f;

};