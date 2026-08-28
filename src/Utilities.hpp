#pragma once
#include <SFML/Graphics.hpp>
#include <cmath> // Required for std::sqrt

/**
 * AI-Generated, accuracy not checked
 */
static void moveTowardsPlayer(float dt, sf::Sprite* spriteToMove, sf::Sprite* targetSprite)
{
    // 1. Get the current position of this sprite
    sf::Vector2f spritePosition = spriteToMove->getPosition();

    // 2. Calculate the vector pointing from the sprite to the player
    sf::Vector2f direction = targetSprite->getPosition() - spritePosition;

    // 3. Calculate the distance (magnitude of the vector)
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // 4. Prevent division by zero if the sprite is already exactly on the player
    if (distance > 1.0f) 
    {
        // Normalize the vector (make its total length equal to 1)
        sf::Vector2f normalizedDirection = direction / distance;

        // 5. Define movement speed (pixels per second)
        float speed = 20.0f; 

        // 6. Move the sprite along the normalized path scaled by speed and dt
        spriteToMove->move(normalizedDirection * speed * dt);
    }
}

static bool checkCollision(sf::Sprite* sprite1, sf::Sprite* sprite2)
{
    sf::FloatRect sprite1Bounds = sprite1->getGlobalBounds();
    sf::FloatRect sprite2Bounds = sprite2->getGlobalBounds();
    std::optional<sf::FloatRect> result = sprite1Bounds.findIntersection(sprite2Bounds);
    return result.has_value();
}