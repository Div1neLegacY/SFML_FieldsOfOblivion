#include <SFML/Graphics.hpp>

const int HEALTH_BAR_WIDTH = 40;
const int HEALTH_BAR_HEIGHT = 10;
const int HEALTH_BAR_POS_X = 10;
const int HEALTH_BAR_POS_Y = 10;

class HealthBar : public sf::RectangleShape
{

public:
    HealthBar(float maxHp) : sf::RectangleShape(sf::Vector2f(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT))
    {
        maxHealth = maxHp;
        currentHealth = maxHp;


        // backgroundBar.setFillColor(sf::Color(50, 50, 50)); // Dark Grey
        // backgroundBar.setPosition(sf::Vector2f(HEALTH_BAR_POS_X, HEALTH_BAR_POS_Y));

        // // Configure the dynamic fluid health display bar
        // foregroundBar.setSize(sf::Vector2f(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT));
        // foregroundBar.setFillColor(sf::Color(46, 204, 113)); // Vibrant Green
        // foregroundBar.setPosition(sf::Vector2f(HEALTH_BAR_POS_X, HEALTH_BAR_POS_Y));
    }

    void update(float currentHp)
    {
        // // Clamp current health bounds safely
        // currentHealth = currentHp;
        // if (currentHealth < 0.f) currentHealth = 0.f;
        // if (currentHealth > maxHealth) currentHealth = maxHealth;

        // // Calculate the modern scale multiplier ratio
        // float healthPercentage = currentHealth / maxHealth;

        // // Shrink the width of the foreground bar seamlessly
        // foregroundBar.setSize(sf::Vector2f(HEALTH_BAR_WIDTH * healthPercentage, foregroundBar.getSize().y));

        // // Optional Color Shift: Turns yellow/red as health drops
        // if (healthPercentage < 0.25f) {
        //     foregroundBar.setFillColor(sf::Color(231, 76, 60));  // Red
        // } else if (healthPercentage < 0.5f) {
        //     foregroundBar.setFillColor(sf::Color(241, 196, 15)); // Yellow
        // } else {
        //     foregroundBar.setFillColor(sf::Color(46, 204, 113));  // Green
        // }
    }


    void draw(sf::RenderWindow& window) {
        //window.draw(backgroundBar);
        //window.draw(foregroundBar);
    }

private:
    //sf::RectangleShape backgroundBar;
    //sf::RectangleShape foregroundBar;
    
    float maxHealth;
    float currentHealth;

};