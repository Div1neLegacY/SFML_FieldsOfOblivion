#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, AnimationSpriteSettings settings)
    : sf::Sprite(texture), settings(settings), currentState(AnimationState::ACTIVE)
{
    int startingX = 0;

    // Set an initial blank sprite if requested. Helpful for attack animations where the
    // player is not attacking and we don't want to show the attack sprite.
    if (settings.initialSpriteBlank)
    {
        frames.emplace_back(sf::IntRect({0, 0}, {0, 0}));
        settings.totalFrames += 1; // Increase total frames to account for the blank frame
    }

    // Cache option: Pre-allocating rect instances
    for (int i = 0; i < settings.totalFrames; ++i)
    {
        auto newFrame = sf::IntRect({startingX, 0}, {settings.frameRect.size.x, settings.frameRect.size.y});
        frames.emplace_back(newFrame);
        startingX += settings.frameRect.size.x;
    }

    if (!frames.empty())
    {
        setTextureRect(frames[currentFrameIndex]);
    }
}

void AnimatedSprite::update(float dt)
{
    if (settings.totalFrames <= 0) return;

    if (cooldownTimer > 0.0f)
    {
        cooldownTimer -= dt;
        if (cooldownTimer > 0.0f) return;
        cooldownTimer = 0.0f;
        currentState = AnimationState::ACTIVE;
    }

    if (currentState == AnimationState::ACTIVE)
    {
        elapsedTime += dt;

        while (elapsedTime >= frameDuration)
        {
            currentFrameIndex = (currentFrameIndex + 1) % settings.totalFrames;
            elapsedTime -= frameDuration;

            if (currentFrameIndex == 0)
            {
                // If animation is setup with a cooldown period, automate switch to IDLE state and start the cooldown timer
                if (settings.animationCooldownDuration > 0.0f)
                {
                    currentState = AnimationState::IDLE;
                    cooldownTimer = settings.animationCooldownDuration;
                    // Reset the set of enemies hit for the next attack cycle
                    enemiesHitThisAttack.clear();
                }
                break;
            }
        }
    }
    else if (currentState == AnimationState::IDLE)
    {
        currentFrameIndex = 0;
        elapsedTime = 0.0f;
    }

    setTextureRect(frames[currentFrameIndex]);

}
