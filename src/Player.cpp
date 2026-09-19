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

    // Create a new weapon. Replaces AnimatedSprite ^^^
    playerWeapons.emplace_back(std::make_unique<Weapon>(
        SPRITE_PLAYER_ATTACK_TEXTURE,
        DEFAULT_PLAYER_ATTACK_ANIMATION_SETTINGS
    ));

    upgradeMenu = std::make_unique<UpgradeMenu>();
    upgradeMenu->setVisible(false);
}

void Player::update(float dt)
{
    // Update player animation sprite
    AnimatedSprite::update(dt);

    // Update all weapon animations
    for (const auto& weapon : playerWeapons)
    {
        weapon->setPosition(camera->getCenter() - sf::Vector2f{30, 30});
        weapon->update(dt);
    }
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

void Player::playerMoveLeft()
{
    sf::Vector2f flippedWeaponScale{ DEFAULT_WEAPON_SCALE.x * -1.0f, DEFAULT_WEAPON_SCALE.y};
    sf::Vector2f flippedPlayerScale{ DEFAULT_PLAYER_SCALE.x * -1.0f, DEFAULT_PLAYER_SCALE.y};
    setScale(flippedPlayerScale);

    // Update all weapon directions
    for (const auto& weapon : playerWeapons)
    {
        // @todo Probably should change to check if player is currently attacking
        // If weapon is currently not active then allow scaling / rotation changes
        if (!weapon->isActive())
        {
            weapon->setScale(flippedWeaponScale);
        }
    }
}

void Player::playerMoveRight()
{
    setScale(DEFAULT_PLAYER_SCALE);

    // Update all weapon directions
    for (const auto& weapon : playerWeapons)
    {
        // @todo Probably should change to check if player is currently attacking
        // If weapon is currently not active then allow scaling / rotation changes
        if (!weapon->isActive())
        {
            weapon->setScale(DEFAULT_WEAPON_SCALE);
        }
    }
}