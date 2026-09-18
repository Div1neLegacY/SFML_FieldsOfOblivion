#include <SFML/Graphics.hpp>
#include "Main.hpp"

class UpgradeMenu : public sf::Transformable, public sf::Drawable
{
private:
    bool visible = false;
    int selectedIndex = 0;
    std::array<sf::Text, 3> menuItems;
    std::array<sf::RectangleShape, 3> buttonShapes;
    sf::RectangleShape backgroundBox;

public:
    UpgradeMenu()
        : menuItems{sf::Text(GAME_FONT), sf::Text(GAME_FONT), sf::Text(GAME_FONT)}
    {
        float totalContentHeight = (UPGRADE_MENU_BUTTON_HEIGHT * 3) + (UPGRADE_MENU_SPACING_BETWEEN_BUTTONS * 2);

        sf::Vector2f backgroundBoxSize{UPGRADE_MENU_BUTTON_WIDTH + (UPGRADE_MENU_PADDING_AROUND_BUTTONS * 2), totalContentHeight + (UPGRADE_MENU_PADDING_AROUND_BUTTONS * 2)};

        // Everything is relative to the game window center
        float localStartX = (WINDOW_CENTER.x + UPGRADE_MENU_PADDING_AROUND_BUTTONS) - (backgroundBoxSize.x / 2);
        float localStartY = (WINDOW_CENTER.y + UPGRADE_MENU_PADDING_AROUND_BUTTONS) - (backgroundBoxSize.y / 2);

        // 1. Setup background container box
        backgroundBox.setSize(backgroundBoxSize);
        backgroundBox.setFillColor(sf::Color(30, 30, 30, 240));
        backgroundBox.setOutlineColor(sf::Color::White);
        backgroundBox.setOutlineThickness(2.f);
        backgroundBox.setPosition(WINDOW_CENTER - (backgroundBoxSize / 2.f));

        std::array<std::string, 3> labels = {"<upgrade_1>", "<upgrade_2>", "<upgrade_3>"};
        for (size_t i = 0; i < 3; i++)
        {
            // Button background
            buttonShapes[i].setSize(sf::Vector2f(200.f, 50.f));
            buttonShapes[i].setFillColor(sf::Color(50, 50, 50));
            buttonShapes[i].setPosition(sf::Vector2f(localStartX, localStartY + i * (UPGRADE_MENU_BUTTON_HEIGHT + UPGRADE_MENU_SPACING_BETWEEN_BUTTONS)));
            // Button text
            menuItems[i].setString(labels[i]);
            menuItems[i].setCharacterSize(24);
            menuItems[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);

            // Center text in button bounds
            sf::FloatRect textRect = menuItems[i].getLocalBounds();
            menuItems[i].setOrigin(textRect.getCenter());
            sf::Vector2f menuItemPosition{buttonShapes[i].getPosition().x + 100.f, buttonShapes[i].getPosition().y + 25.f};
            menuItems[i].setPosition(menuItemPosition);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!visible)
        {
            return;
        }

        // Apply the menu object's transformation matrix (position, rotation, scale) to children
        states.transform *= getTransform();

        target.draw(backgroundBox, states);
        for (size_t i = 0; i < 3; i++) {
            target.draw(buttonShapes[i], states);
            target.draw(menuItems[i], states);
        }
    }

    void updateMouse(sf::Vector2f mousePos)
    {
        int hoveredIndex = -1;

        for (std::size_t i = 0; i < buttonShapes.size(); ++i)
        {
            if (buttonShapes[i].getGlobalBounds().contains(mousePos))
            {
                hoveredIndex = static_cast<int>(i);
                break;
            }
        }

        // If not hovering over a button or a different button from the previously selected
        if (hoveredIndex == -1 || hoveredIndex == selectedIndex)
        {
            return;
        }

        // Deselect previously selected, then select new
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex = hoveredIndex;
        menuItems[selectedIndex].setFillColor(sf::Color::Yellow);
    }

    int handleMouseClick(sf::Vector2f mousePos)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (buttonShapes[i].getGlobalBounds().contains(mousePos))
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void setVisible(bool visible)
    {
        this->visible = visible;
    }

    bool isVisible() const
    {
        return visible;
    }
};