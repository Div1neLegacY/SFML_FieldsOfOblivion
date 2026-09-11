#pragma once

#include "Main.hpp"
#include "HealthBar.hpp"
#include "AnimatedSprite.hpp"

class Player : public AnimatedSprite
{
public:
    Player();
    void update(float dt);

    std::unique_ptr<sf::View> camera;
    //HealthBar* healthBar;
    std::unique_ptr<AnimatedSprite> attackAnimationSprite;
private:
    // Timer to track the cooldown period between attacks
    float attackTimer = 0.0f;

};