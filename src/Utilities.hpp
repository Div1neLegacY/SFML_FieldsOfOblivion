#pragma once
#include <SFML/Graphics.hpp>
#include <cmath> // Required for std::sqrt
#include <cstdlib>
#include <ctime>
#include "Main.hpp"

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

        // 6. Move the sprite along the normalized path scaled by speed and dt
        spriteToMove->move(normalizedDirection * DEFAULT_ENEMY_SPEED * dt);
    }
}

static bool checkCollision(sf::Sprite* sprite1, sf::Sprite* sprite2)
{
    sf::FloatRect sprite1Bounds = sprite1->getGlobalBounds();
    sf::FloatRect sprite2Bounds = sprite2->getGlobalBounds();
    std::optional<sf::FloatRect> result = sprite1Bounds.findIntersection(sprite2Bounds);
    return result.has_value();
}

/**
 * Damage calculation function
 * Final value = (base + flat) * (1 + percentage) * multiplier
 */
static float calculateDamage(int base, float flat, float percentage, float multiplier)
{
    float totalBase = static_cast<float>(base + flat);
    float totalBaseWithPercentage = totalBase * (1 + percentage);
    float totalBaseWithMultiplier = totalBaseWithPercentage * multiplier;
    return totalBaseWithMultiplier;
}

/**
 * AI-Generated, accuracy not checked
 */
static sf::Vector2f randomPointOffScreen()
{
    // Keep a small margin outside the visible window so the sprite fully appears off-screen
    const float margin = 100.0f;

    // Seed once if this utility is being used before the rest of the game seeds randomness.
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    const int side = std::rand() % 4;
    const float randomX = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * WINDOW_WIDTH;
    const float randomY = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * WINDOW_HEIGHT;

    switch (side)
    {
        case 0: // Top edge
            return sf::Vector2f(randomX, -margin);
        case 1: // Bottom edge
            return sf::Vector2f(randomX, WINDOW_HEIGHT + margin);
        case 2: // Left edge
            return sf::Vector2f(-margin, randomY);
        default: // Right edge
            return sf::Vector2f(WINDOW_WIDTH + margin, randomY);
    }
}