#include "AnimatedSprite.hpp"

void AnimatedSprite::update(float dt)
{
    if (totalFrames <= 0) return;

    if (cooldownTimer > 0.0f)
    {
        cooldownTimer -= dt;
        if (cooldownTimer > 0.0f) return;
        cooldownTimer = 0.0f;
    }

    if (currentState == AnimationState::ACTIVE)
    {
        elapsedTime += dt;

        while (elapsedTime >= frameDuration)
        {
            currentFrameIndex = (currentFrameIndex + 1) % totalFrames;
            elapsedTime -= frameDuration;

            if (currentFrameIndex == 0)
            {
                cooldownTimer = animationCooldownDuration;
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
