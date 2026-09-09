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
    AnimatedSprite(const sf::Texture& texture, int totalFrames, float animationCooldownDuration = 0.0f, int frameWidth = GLOBAL_SPRITE_FRAME_WIDTH, int frameHeight = GLOBAL_SPRITE_FRAME_HEIGHT)
        : sf::Sprite(texture), currentFrameIndex(0), 
          totalFrames(totalFrames), animationCooldownDuration(animationCooldownDuration)
    {
        currentState = AnimationState::ACTIVE;
        
        int startingX = 0;

        // Cache option: Pre-allocating rect instances
        for (int i = 0; i < totalFrames; ++i)
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

    void update(float dt)
    {
        if (totalFrames <= 0) return;

        // if (cooldownTimer > 0.0f)
        // {
        //     cooldownTimer -= dt;
        //     return;
        // }

        if (currentState == AnimationState::ACTIVE)
        {
            // Accumulate time passed since last frame
            elapsedTime += dt;

            // Check if enough time has passed to advance to the next frame
            if (elapsedTime >= frameDuration)
            {
                currentFrameIndex = (currentFrameIndex + 1) % totalFrames;
                // Reset accumulator while keeping overflow
                elapsedTime -= frameDuration;
            }
        }
        else if (currentState == AnimationState::IDLE)
        {
            currentFrameIndex = 0;
            // Reset time so moving starts fresh instantly
            elapsedTime = 0.0f;
        }

        // Setting the texture rect from cache
        setTextureRect(frames[currentFrameIndex]);

        // Reset the timer to trigger the cooldown period
        //cooldownTimer = animationCooldownDuration; 
    }
};