#pragma once

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "Upgrades.hpp"

struct BaseWeaponStats
{
    // icon;
    sf::String weapon;
    sf::String description;
    float baseDamage;
    uint8_t maxLevel;
    uint8_t rarity;
    sf::String effects;
    sf::String unlockRequirements;
};

struct BaseWeapon
{
    BaseWeaponStats stats;
    AnimationSpriteSettings animationSettings;
};

class Weapon : public AnimatedSprite
{
public:
    /**
     * Constructor
     */
    explicit Weapon(const sf::Texture& texture, AnimationSpriteSettings settings);

    /**
     * Disallow construction from a temporary object
     */
    explicit Weapon(const sf::Texture&& texture, AnimationSpriteSettings settings) = delete;

    void update(float dt, float animationCooldownDuration = 0.f) override;

private:
    /**
     * Member Variables
     */

};