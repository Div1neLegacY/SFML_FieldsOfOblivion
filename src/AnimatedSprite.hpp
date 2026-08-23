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
        std::cout << "Set state to: " << nextState << std::endl;
        currentState = nextState;
    }

    void update()
    {
        if (totalFrames <= 0) return;

        if (currentState == AnimationState::MOVING)
        {
            currentFrameIndex = (currentFrameIndex + 1) % totalFrames;
        }
        else if (currentState == AnimationState::IDLE)
        {
            currentFrameIndex = 0;
        }

        // Setting the texture rect from cache
        setTextureRect(frames[currentFrameIndex]);
    }
};