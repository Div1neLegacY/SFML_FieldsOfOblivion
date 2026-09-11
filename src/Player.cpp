#include "Player.hpp"

Player::Player() : AnimatedSprite(SPRITE_PLAYER_TEXTURE, get_sprite(SPRITE_PLAYER).frameCount)
{
    // Save pointer later to do more with the sprite
	setScale(sf::Vector2f{2, 2});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	setOrigin(getLocalBounds().getCenter());
	setPosition(WINDOW_CENTER);
    camera = std::make_unique<sf::View>(sf::FloatRect({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    //this->healthBar = new HealthBar(100.f);

    attackAnimationSprite = std::make_unique<AnimatedSprite>(
        SPRITE_PLAYER_ATTACK_TEXTURE,
        get_sprite(SPRITE_PLAYER_ATTACK).frameCount,
        ATTACK_COOLDOWN,
        64, 64,
        true
    );
    attackAnimationSprite->setScale(sf::Vector2f{4, 2});
}

void Player::update(float dt)
{
    // Update player animation sprite
    AnimatedSprite::update(dt);

    // Update attack animation sprite
    attackAnimationSprite->update(dt);
    attackAnimationSprite->setPosition(camera->getCenter() - sf::Vector2f{30, 30});
} 