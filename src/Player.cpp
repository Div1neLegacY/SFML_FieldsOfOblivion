#include "Player.hpp"
#include "Utilities.hpp"

Player::Player() : AnimatedSprite(SPRITE_PLAYER_TEXTURE, DEFAULT_PLAYER_ANIMATION_SETTINGS), currentLevelBracket(LEVEL_BRACKETS.begin())
{
    // Save pointer later to do more with the sprite
	setScale(sf::Vector2f{2, 2});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	setOrigin(getLocalBounds().getCenter());
	setPosition(WINDOW_CENTER);
    camera = std::make_unique<sf::View>(sf::FloatRect({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    //this->healthBar = new HealthBar(100.f);

    attackAnimationSprite = std::make_unique<AnimatedSprite>(
        SPRITE_PLAYER_ATTACK_TEXTURE,
        DEFAULT_PLAYER_ATTACK_ANIMATION_SETTINGS);
    attackAnimationSprite->setScale(sf::Vector2f{4, 2});

    upgradeMenu = std::make_unique<UpgradeMenu>(300.f, 20.f);
    upgradeMenu->setVisible(false);
}

void Player::update(float dt)
{
    // Update player animation sprite
    AnimatedSprite::update(dt);

    // Update attack animation sprite
    attackAnimationSprite->update(dt);
    attackAnimationSprite->setPosition(camera->getCenter() - sf::Vector2f{30, 30});
}

void Player::addExp(int amount)
{
    currentExp += amount;

    printf("currentExp: %d\n", currentExp);
    fflush(stdout);

    // Level-up player if they have enough experience
    if (currentExp == currentLevelBracket->second)
    {
        upgradeMenu->setVisible(true);
        currentExp = 0;
        currentPlayerLevel++;
        printf("currentPlayerLevel: %d\n", currentPlayerLevel);
        fflush(stdout);

        // @TODO wait on upgradeMenu for input

        // If bracket iterator is not at end of defined bracket list and
        // current level reaches next bracket, then advance to next
        if (currentLevelBracket != LEVEL_BRACKETS.end() && currentPlayerLevel == std::next(currentLevelBracket)->first)
        {
            currentLevelBracket++; // Forward iterators only move forward
            printf("currentLevelBracket->first: %d\n", currentLevelBracket->first);
            fflush(stdout);
        }
    }
}