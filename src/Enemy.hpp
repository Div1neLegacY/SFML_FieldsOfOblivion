#pragma once

#include "Main.hpp"
#include "AnimatedSprite.hpp"

struct EnemySettings
{
    
};

class Enemy : public AnimatedSprite
{
private:
    EnemySettings settings;
    int health = 30;
    int enemyID; // Unique identifier for the enemy, useful for tracking hits
public:
    Enemy(int enemyID, EnemySettings settings = {});
    void update(float dt);
    void damage(int amount);
    bool isDead();
    int getId() const { return enemyID; }
};