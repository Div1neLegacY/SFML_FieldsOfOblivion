#include "Enemy.hpp"

Enemy::Enemy(int enemyID, EnemySettings settings)
    : AnimatedSprite(SPRITE_ENEMY_TEXTURE, DEFAULT_ENEMY_ANIMATION_SETTINGS), enemyID(enemyID), settings(settings)
{
    // Save pointer later to do more with the sprite
	setScale(sf::Vector2f{2, 2});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	setOrigin(getLocalBounds().getCenter());
}

void Enemy::update(float dt)
{
    // @TODO
    // Update enemy animation sprite
    //AnimatedSprite::update(dt);
}

void Enemy::damage(int amount)
{
    health -= amount;
    // @TODO: Flash enemy sprite to indicate damage taken
}

bool Enemy::isDead()
{
    return health <= 0;
}