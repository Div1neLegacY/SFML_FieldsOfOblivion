#include "Weapon.hpp"

Weapon::Weapon(const sf::Texture& texture, AnimationSpriteSettings settings)
    : AnimatedSprite(texture, settings)
{
}

void Weapon::update(float dt, float weaponCooldown)
{
    AnimatedSprite::update(dt, weaponCooldown);
}