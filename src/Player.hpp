#pragma once

#include "Main.hpp"
#include "HealthBar.hpp"
#include "AnimatedSprite.hpp"

class Player : public AnimatedSprite
{
public:
    Player();
    void update(float dt);
    void addExp(int amount);

    std::unique_ptr<sf::View> camera;
    //HealthBar* healthBar;
    int currentPlayerLevel = 0;
    std::forward_list<std::pair<unsigned int, unsigned int>>::const_iterator currentLevelBracket;
    int currentExp = 0;
    std::unique_ptr<AnimatedSprite> attackAnimationSprite;
private:
    // Timer to track the cooldown period between attacks
    float attackTimer = 0.0f;

};