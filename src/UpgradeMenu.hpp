#include <SFML/Graphics.hpp>

class UpgradeMenu : public sf::Transformable, public sf::Drawable
{
private:
    bool visible = true;
    int selectedIndex = 0;
    std::array<sf::Text, 3> menuItems;
    std::array<sf::RectangleShape, 3> buttonShapes;
    sf::RectangleShape backgroundBox;

public:
    UpgradeMenu(float width, float height)
        : menuItems{sf::Text(GAME_FONT), sf::Text(GAME_FONT), sf::Text(GAME_FONT)}
    {
        float buttonWidth = 200.f;
        float buttonHeight = 50.f;
        float spacing = 20.f;
        float padding = 30.f;

        float totalContentHeight = (buttonHeight * 3) + (spacing * 2);

        sf::Vector2f backgroundBoxSize{buttonWidth + (padding * 2), totalContentHeight + (padding * 2)};

        // Everything is relative to the menu's local origin (0, 0)
        float localStartX = (WINDOW_CENTER.x + padding) - (backgroundBoxSize.x / 2);
        float localStartY = (WINDOW_CENTER.y + padding) - (backgroundBoxSize.y / 2);

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
            buttonShapes[i].setPosition(sf::Vector2f(localStartX, localStartY + i * (buttonHeight + spacing)));
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
        for (size_t i = 0; i < 3; i++)
        {
            if (buttonShapes[i].getGlobalBounds().contains(mousePos))
            {
                menuItems[selectedIndex].setFillColor(sf::Color::White);
                selectedIndex = static_cast<int>(i);
                menuItems[selectedIndex].setFillColor(sf::Color::Yellow);
            }
        }
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