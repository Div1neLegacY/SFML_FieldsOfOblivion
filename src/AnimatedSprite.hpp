#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Main.hpp"
#include <iostream>

enum AnimationState
{
    IDLE,
    MOVING,
};

class AnimatedSprite : public sf::Sprite {
private:
    std::vector<sf::IntRect> frames;
    std::size_t currentFrameIndex;
    int totalFrames;
    AnimationState currentState;
    float elapsedTime = 0.0f;
    // Change this to adjust animation speed (e.g., 0.1s per frame)
    float frameDuration = 0.05f;


public:
    AnimatedSprite(const sf::Texture& texture, int totalFrames)
        : sf::Sprite(texture), currentFrameIndex(0), 
          totalFrames(totalFrames)
    {
        currentState = AnimationState::IDLE;
        
        int startingX = 0;

        // Cache option: Pre-allocating rect instances
        for (int i = 0; i < totalFrames; ++i)
        {
            frames.emplace_back(sf::Vector2i(startingX, 0), sf::Vector2i(GLOBAL_SPRITE_FRAME_WIDTH, GLOBAL_SPRITE_FRAME_HEIGHT));
            startingX += GLOBAL_SPRITE_FRAME_WIDTH;
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

        if (currentState == AnimationState::MOVING)
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
    }
};