#include "Player.hpp"

Player::Player()
{
    // Save pointer later to do more with the sprite
    this->sprite = new AnimatedSprite(SPRITE_PLAYER_TEXTURE, get_sprite(SPRITE_PLAYER).frameCount);
	this->sprite->setScale(sf::Vector2f{2, 2});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	this->sprite->setOrigin(sprite->getLocalBounds().getCenter());
	this->sprite->setPosition(WINDOW_CENTER);
    this->camera = new sf::View(sf::FloatRect({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    //this->healthBar = new HealthBar(100.f);

    attackAnimationSprite = std::make_unique<AnimatedSprite>(SPRITE_PLAYER_ATTACK_TEXTURE, get_sprite(SPRITE_PLAYER_ATTACK).frameCount, ATTACK_COOLDOWN, 64, 64);
}

Player::~Player()
{
    delete camera, sprite;//, healthBar;
}

void Player::update(float dt)
{
    attackAnimationSprite->update(dt);
    attackAnimationSprite->setPosition(sprite->getPosition());
} 