#pragma once

#include "Main.hpp"
#include "HealthBar.hpp"
#include "AnimatedSprite.hpp"
#include "Weapon.hpp"
#include "UpgradeMenu.hpp"

class Player : public AnimatedSprite
{
public:
    Player();
    void update(float dt);
    void addExp(int amount);

    /**
     * Logic for moving player left
     */
    void playerMoveLeft();

    /**
     * Logic for moving player right
     */
    void playerMoveRight();

    std::unique_ptr<sf::View> camera;
    //HealthBar* healthBar;
    std::unique_ptr<UpgradeMenu> upgradeMenu;
    int currentPlayerLevel = 0;
    std::forward_list<std::pair<unsigned int, unsigned int>>::const_iterator currentLevelBracket;
    int currentExp = 0;

    // Player weapons
    std::vector<std::unique_ptr<Weapon>> playerWeapons;
private:
    // Timer to track the cooldown period between attacks
    float attackTimer = 0.0f;

};