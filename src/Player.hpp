#pragma once

#include "Main.hpp"
#include "HealthBar.hpp"
#include "AnimatedSprite.hpp"
#include "Weapon.hpp"
#include "UpgradeMenu.hpp"

enum class PlayerState
{
    NORMAL,
    INVINCIBLE,
};

class Player : public AnimatedSprite
{
public:
    /**
     * Constructor
     */
    Player();

    void update(float dt);

    /**
     * Adds exp to current player level progression
     */
    void addExp(int amount);

    /**
     * Applies upgrade modifies to player
     */
    void applyUpgrade(Upgrade upgrade);

    /**
     * Logic for moving player left
     */
    void playerMoveLeft();

    /**
     * Logic for moving player right
     */
    void playerMoveRight();

    float getPlayerDamage() const
    {
        return currentWeaponDamage;
    }

    bool isPlayerInvincible() const
    {
        return playerState == PlayerState::INVINCIBLE;
    }

    void startInvincibilityTimer()
    {
        invincibilityTimer = INVINCIBILITY_DURATION;
        playerState = PlayerState::INVINCIBLE;
    }

    std::unique_ptr<sf::View> camera;
    //HealthBar* healthBar;
    std::unique_ptr<UpgradeMenu> upgradeMenu;
    int currentPlayerLevel = 0;
    std::forward_list<std::pair<unsigned int, unsigned int>>::const_iterator currentLevelBracket;
    int currentExp = 0;

    // Player weapons
    std::vector<std::unique_ptr<Weapon>> playerWeapons;

private:
    /**
     * Member Variables
     */
    PlayerState playerState = PlayerState::NORMAL;
    float invincibilityTimer = 0.0f; // Timer to track the player's invincibility period
    float attackTimer = 0.0f;        // Timer to track the cooldown period between attacks
    float currentWeaponDamage = DEFAULT_WEAPON_DAMAGE;      // Keeps track of player's damage
    float currentWeaponCooldown = DEFAULT_ATTACK_COOLDOWN;  // Keeps track of player's cooldown
    sf::Vector2f currentWeaponScale = DEFAULT_WEAPON_SCALE; // Keeps track of player's range
};