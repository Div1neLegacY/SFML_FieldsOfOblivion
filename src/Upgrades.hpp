#pragma once

enum UpgradeID
{
    DAMAGE,
    RANGE,
    COOLDOWN,
};

enum EffectType
{
    FLAT,
    PERCENTAGE,
    MULTIPLIER,
};

struct Upgrade
{
    UpgradeID upgradeId;     // Identifier type of upgrade
    unsigned short MaxLevel; // Max level of upgrade
    EffectType effectType;   // How the effect is applied in math operations
    float effectValue;       // How much is applied to the effect in operations
};