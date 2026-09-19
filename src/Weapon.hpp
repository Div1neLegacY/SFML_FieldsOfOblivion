#pragma once

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

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

    void update(float dt) override;
};