#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <set>

enum AnimationState
{
    IDLE,
    ACTIVE,
};

struct AnimationSpriteSettings
{
    // Total number of frames in the sprite animation
    int totalFrames;
    // Rectangle defining the frame size of the sprite
    sf::IntRect frameRect;
    sf::Vector2f defaultScale;
    sf::Vector2f positionOffset;
    // (Optional) Initialize frames with a blank sprite.
    // Useful for attack animations where the player is not attacking and we don't want to show the attack sprite.
    bool initialSpriteBlank = false;
    // @TODO
    // Duplicates animation and mirrors it. Good for multi-directional weapons
    bool mirrorAnimation = false;
};

class AnimatedSprite : public sf::Sprite {
private:
    std::vector<sf::IntRect> frames;
    AnimationSpriteSettings settings;
    AnimationState currentState;
    int currentFrameIndex = 0;
    float elapsedTime = 0.0f;
    float frameDuration = 0.04f;
    float cooldownTimer = 0.0f; // Timer for tracking cooldown period

public:
    // @TODO Move into Attack animation sprite class?
    // Tracks unique IDs of enemies hit during the current attack cycle
    std::set<int> enemiesHitThisAttack;

public:
    AnimatedSprite(const sf::Texture& texture, AnimationSpriteSettings settings);

    void setState(AnimationState nextState)
    {
        currentState = nextState;
    }

    bool isActive()
    {
        return currentState == AnimationState::ACTIVE;
    }

    sf::Vector2f getOffset()
    {
        return settings.positionOffset;
    }

    virtual void update(float dt, float animationCooldownDuration = 0.f);
};