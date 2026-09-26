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
        SPRITE_WEAPON_SWORD_TEXTURE,
        PLAYER_SWORD_WEAPON_ANIMATION_SETTINGS
    ));

    playerWeapons.emplace_back(std::make_unique<Weapon>(
        SPRITE_WEAPON_BLAZE_BOOK_TEXTURE,
        PLAYER_BLAZE_BOOK_WEAPON_ANIMATION_SETTINGS
    ));

    upgradeMenu = std::make_unique<UpgradeMenu>();
    upgradeMenu->setVisible(false);
}

void Player::update(float dt)
{
    // Update player animation sprite
    AnimatedSprite::update(dt);

    // Tick down the invincibility timer (if needed)
    if (invincibilityTimer > 0.0f)
    {
        invincibilityTimer = std::max(0.0f, invincibilityTimer - dt);

        if (invincibilityTimer == 0.0f)
        {
            playerState = PlayerState::NORMAL;
        }
    }

    // Update all weapon animations
    for (const auto& weapon : playerWeapons)
    {
        const sf::Vector2f offset = weapon->getOffset();
        const float facingDirection = weapon->getScale().x < 0.f ? -1.f : 1.f;
        const sf::Vector2f weaponPosition{
            camera->getCenter().x - (offset.x * facingDirection),
            camera->getCenter().y - offset.y
        };
        weapon->setPosition(weaponPosition);
        weapon->update(dt, currentWeaponCooldown);
    }
}

void Player::addExp(int amount)
{
    currentExp += amount;

    printf("currentExp: %d\n", currentExp);
    fflush(stdout);

    // Level-up player if they have enough experience
    while (currentExp >= currentLevelBracket->second)
    {
        upgradeMenu->setVisible(true);
        currentExp -= currentLevelBracket->second;
        currentPlayerLevel++;
        printf("currentPlayerLevel: %d\n", currentPlayerLevel);
        fflush(stdout);

        // Stop leveling once the final bracket has been reached.
        auto nextLevelBracket = std::next(currentLevelBracket);
        if (nextLevelBracket == LEVEL_BRACKETS.end())
        {
            return;
        }

        // If current level reaches the next bracket, advance to it.
        if (currentPlayerLevel == nextLevelBracket->first)
        {
            currentLevelBracket = nextLevelBracket;
            printf("currentLevelBracket->first: %d\n", currentLevelBracket->first);
            fflush(stdout);
        }
    }
}

void Player::applyUpgrade(Upgrade upgrade)
{
    switch(upgrade.upgradeId)
    {
        case UpgradeID::DAMAGE:
        {
            // Convert percentage to a scaling multiplier (1.0f + 0.20f = 1.20f)
            float scalar = 1.0f + (upgrade.effectValue / 100.0f);

            currentWeaponDamage *= scalar;
            printf("currentWeaponDamage: { %f }", currentWeaponDamage);
            break;
        }
        case UpgradeID::RANGE:
        {
            // Convert percentage to a scaling multiplier (1.0f + 0.20f = 1.20f)
            float scalar = 1.0f + (upgrade.effectValue / 100.0f);

            // Update the vector
            // @TODO comment out till we specify weapon to upgrade range
            // currentWeaponScale *= scalar;
            // printf("currentWeaponScale: { %f, %f }", currentWeaponScale.x, currentWeaponScale.y);
            // for (auto& weapon : playerWeapons)
            // {
            //     weapon->setScale(currentWeaponScale);
            // }
            // break;
        }
        case UpgradeID::COOLDOWN:
        {
            // Convert percentage to a scaling multiplier (1.0f - 0.20f = 0.80f)
            float scalar = 1.0f - (upgrade.effectValue / 100.0f);

            // Update the vector
            currentWeaponCooldown *= scalar;
            printf("currentWeaponCooldown: { %f }", currentWeaponCooldown);
            break;
        }
    }
}

void Player::playerMoveLeft()
{
    sf::Vector2f flippedPlayerScale{ DEFAULT_PLAYER_SCALE.x * -1.0f, DEFAULT_PLAYER_SCALE.y };
    setScale(flippedPlayerScale);

    // Update all weapon directions
    for (const auto& weapon : playerWeapons)
    {
        // @todo Probably should change to check if player is currently attacking
        // If weapon is currently not active then allow scaling / rotation changes
        // We don't want weapon animation to update direction mid-attack
        if (!weapon->isActive())
        {
            sf::Vector2f currentWeaponScale = weapon->getScale();
            sf::Vector2f flippedWeaponScale{ -std::abs(currentWeaponScale.x), currentWeaponScale.y };
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
        // If weapon is currently not active then allow scaling / rotation changes.
        // We don't want weapon animation to update direction mid-attack
        if (!weapon->isActive())
        {
            sf::Vector2f currentWeaponScale = weapon->getScale();
            sf::Vector2f flippedWeaponScale{ std::abs(currentWeaponScale.x), currentWeaponScale.y };
            weapon->setScale(flippedWeaponScale);
        }
    }
}