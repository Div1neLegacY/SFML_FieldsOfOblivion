#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <filesystem>

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
	void updateWorld();
	void updatePollEvents();
	// **DLL Hot Reloading**
	void updateDll();
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
	void initWorld();
	//void initSystems();

	//void initPlayer();
	//void initEnemies();

    //Window
	sf::RenderWindow* window;
    // Main menu Drawable elements
    std::vector<sf::Drawable*> mainMenuElements;
    // Elements we want to keep pointers to for additional manipulation
    sf::Sprite* playButton;
    sf::Sprite* player;
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