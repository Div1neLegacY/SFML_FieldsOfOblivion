#pragma once

#include "Main.hpp"
#include "AnimatedSprite.hpp"

struct EnemySettings
{
    float damageDuration = 0.1f; // Duration for which the enemy is in a damaged state
};

enum class EnemyState
{
    NORMAL,
    DAMAGED,
};

class Enemy : public AnimatedSprite
{
private:
    EnemySettings settings;
    int health = 30;
    int enemyID; // Unique identifier for the enemy, useful for tracking hits
    float damageTimer = 0.0f; // Timer to track how long the enemy has been in a damaged state
    EnemyState enemyState = EnemyState::NORMAL; // Current state of the enemy
public:
    Enemy(int enemyID, EnemySettings settings = {});
    void update(float dt);
    void damage(int amount);
    bool isDead();
    bool isDamaged() const { return enemyState == EnemyState::DAMAGED; }
    int getId() const { return enemyID; }
};