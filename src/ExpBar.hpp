#include <SFML/Graphics.hpp>

class ExpBar
{
private:
    sf::RectangleShape background;
    sf::RectangleShape fill;
    sf::Text levelText; // Text object to display current level
    float maxWidth;

public:
    ExpBar(float width, float height)
        : levelText(GAME_FONT, "LVL: 1", 16)
    {
        maxWidth = width;

        // Background styling (dark gray)
        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(50, 50, 50));
        background.setPosition(WINDOW_CENTER_TOP - sf::Vector2f(width / 2, 0));

        // Fill styling (bright yellow/gold for EXP)
        fill.setSize(sf::Vector2f(0.f, height));
        fill.setFillColor(sf::Color(255, 215, 0));
        fill.setPosition(WINDOW_CENTER_TOP - sf::Vector2f(width / 2, 0));

        // Level text styling
        levelText.setFillColor(sf::Color::White);

        // Positioned 5 pixels below the bar (y + height + 5)
        levelText.setPosition(WINDOW_CENTER_TOP + sf::Vector2f(-width / 2, height + 5.f));
        levelText.setString("LVL: 0");
    }

    // Call this whenever current EXP or max EXP changes
    void update(int currentExp, int maxExp, int currentLevel) {
        if (maxExp <= 0) return;
        float percent = static_cast<float>(currentExp) / static_cast<float>(maxExp);
        if (percent > 1.f) percent = 1.f;
        
        fill.setSize(sf::Vector2f(maxWidth * percent, fill.getSize().y));

        // Update the level display text
        levelText.setString("LVL: " + std::to_string(currentLevel));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(fill);
        window.draw(levelText); // Draw the text
    }
};