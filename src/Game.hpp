#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>

enum class GameState {
    MainMenu,
    Playing,
    Paused
};

class Game
{
public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	//void updateInput();
	//void updateGUI();
	//void updateWorld();
	//void updateCollision();
	//void updateBullets();
	//void updateEnemies();
	//void updateCombat();
	void update();

	//void renderGUI();
	//void renderWorld();
	void render();

    bool isOpen() const
    {
        return window && window->isOpen();
    }

private:
    //Private functions
	void initMainMenu();
	//void initGUI();
	//void initWorld();
	//void initSystems();

	//void initPlayer();
	//void initEnemies();

    //Window
	sf::RenderWindow* window;
    // Main menu Drawable elements
    std::vector<sf::Drawable*> mainMenuElements;
    // Elements we want to keep pointers to for additional manipulation
    sf::Sprite* playButton;
    GameState currentState = GameState::MainMenu;

	//Resources
	//std::map<std::string, sf::Texture*> textures;
	//std::vector<Bullet*> bullets;

	//GUI
	//sf::Font font;

	//World
	//sf::Texture worldBackgroundTex;
	//sf::Sprite worldBackground;

	//Player
	//Player* player;

	//PlayerGUI
	//sf::RectangleShape playerHpBar;
	//sf::RectangleShape playerHpBarBack;

	//Enemies
	//float spawnTimer;
	//float spawnTimerMax;
	//std::vector<Enemy*> enemies;
};