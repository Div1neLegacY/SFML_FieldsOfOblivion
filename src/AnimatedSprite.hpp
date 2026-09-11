#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Main.hpp"
#include <iostream>

enum AnimationState
{
    IDLE,
    ACTIVE,
};

class AnimatedSprite : public sf::Sprite {
private:
    std::vector<sf::IntRect> frames;
    std::size_t currentFrameIndex;
    int totalFrames;
    AnimationState currentState;
    float elapsedTime = 0.0f;
    float frameDuration = 0.05f;
    float cooldownTimer = 0.0f; // Timer for tracking cooldown period
    float animationCooldownDuration; // Optional cooldown period after completing a full animation cycle


public:
    AnimatedSprite(
        const sf::Texture& texture,
        int totalFrames,
        float animationCooldownDuration = 0.0f,
        int frameWidth = GLOBAL_SPRITE_FRAME_WIDTH,
        int frameHeight = GLOBAL_SPRITE_FRAME_HEIGHT,
        bool initialSpriteBlank = false)
            : sf::Sprite(texture), currentFrameIndex(0), 
            totalFrames(totalFrames), animationCooldownDuration(animationCooldownDuration)
    {
        currentState = AnimationState::ACTIVE;

        int startingX = 0;

        // Set an initial blank sprite if requested. Helpful for attack animations where the
        // player is not attacking and we don't want to show the attack sprite.
        if (initialSpriteBlank)
        {
            frames.emplace_back(sf::Vector2i(0, 0), sf::Vector2i(0, 0));
            this->totalFrames += 1; // Increase total frames to account for the blank frame
        }

        // Cache option: Pre-allocating rect instances
        for (int i = 0; i < this->totalFrames; ++i)
        {
            frames.emplace_back(sf::Vector2i(startingX, 0), sf::Vector2i(frameWidth, frameHeight));
            startingX += frameWidth;
        }

        if (!frames.empty())
        {
            setTextureRect(frames[currentFrameIndex]);
        }
    }

    void setState(AnimationState nextState)
    {
        currentState = nextState;
    }

    void update(float dt);
};