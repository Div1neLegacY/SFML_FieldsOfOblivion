#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <filesystem>
#include "AnimatedSprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ExpBar.hpp"

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

	void updateInput();
	void updateGUI();
	void updateBackground();
	void updateEnemies(float dt);
	void updateWorld(float dt);
	void updatePollEvents();
	//void updateCollision();
	//void updateBullets();
	//void updateEnemies();
	//void updateCombat();
	void update(float dt);

	//void renderGUI();
	//void renderWorld();
	void render();
	void renderPlaying();
	void renderEnemies();

    bool isOpen() const
    {
        return window && window->isOpen();
    }

private:
    //Private functions
	void initMainMenu();
	void initPauseMenu();
	void updatePauseMenu();
	//void initGUI();
	void initWorld();
	//void initSystems();

	//void initPlayer();
	//void initEnemies();

    //Window
	sf::RenderWindow* window;
    // Main menu Drawable elements
    std::vector<sf::Drawable*> mainMenuElements;
	// "Playing" Game state UI elements
	std::vector<sf::Drawable*> playingUIElements;
    // Elements we want to keep pointers to for additional manipulation
    sf::Sprite* playButton;

	// Health Bar
	sf::RectangleShape* healthBar;
	ExpBar* expBar;
	int currentHealth = MAX_HEALTH;
	float invincibilityTimer = 0.0f;

	// @todo Do later
    //std::unique_ptr<AnimatedSprite> player;
	Player* player;
	// Enemies
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<sf::Sprite>> expOrbs;

	std::vector<sf::Drawable*> pauseMenuElements;
	sf::Text* pauseMenuText;
	sf::Text* title;

	//Camera
    GameState currentState = GameState::MainMenu;

	//Array<IRect, NUM_OF_TILE_ROWS * NUM_OF_TILE_COLUMNS> backgroundTiles;
	std::vector<sf::Sprite> backgroundSprites;

	// **DLL Hot Reloading**
    using SetTitleFn = void (*)(sf::Text&, const char*);
    void* dllHandle = nullptr;
    SetTitleFn dllSetTitle = nullptr;
    std::filesystem::file_time_type dllLastWrite{};
	
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