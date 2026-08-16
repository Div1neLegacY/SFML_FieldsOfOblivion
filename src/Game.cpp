#include "Assets.hpp"
#include "Main.hpp"
#include "Game.hpp"
#include "GameHotReload.hpp"
#include <filesystem>
#include <iostream>


Game::Game()
{
    window = new sf::RenderWindow( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Fields of Oblivion" );

    initMainMenu();
}

Game::~Game()
{
    delete window;
}

void Game::run()
{
	// while (this->window->isOpen())
	// {
	// 	this->updatePollEvents();

	// 	if(this->player->getHp() > 0)
	// 		this->update();

	// 	this->render();
	// }
}

void Game::initMainMenu()
{
    std::cout << "Initializing Main Menu..." << std::endl;
    sf::Text* title = new sf::Text(GAME_TITLE_FONT, GAME_TITLE, 50);
    title->setFillColor(sf::Color::White);
    // @todo Is this really necessary? It seems to be a workaround for a bug in SFML 2.5.1 where the text's origin is not set correctly when using a custom font.
	// Center the title's origin to allow easy horizontal alignment
	title->setOrigin(title->getLocalBounds().getCenter());

	// Position: Horizontal center, 80 pixels down from the top edge
	title->setPosition(sf::Vector2f{WINDOW_WIDTH / 2.0f, 80.0f});

    sf::Sprite* playButton = new sf::Sprite(SPRITE_BUTTON_PLAY_TEXTURE);
	playButton->setScale(sf::Vector2f{5, 5});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	playButton->setOrigin(playButton->getLocalBounds().getCenter());
	playButton->setPosition(sf::Vector2f{WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f});
    // Save pointer later to do more with the button (like hover detection)
    this->playButton = playButton;

    mainMenuElements.push_back(title);
    mainMenuElements.push_back(playButton);
    std::cout << "Main Menu Initialized." << std::endl;
}

void Game::initWorld()
{
    /**
     * GENERATE BACKGROUND TILES
     */
    // Start background tile positioning at the left-side of the window
    float startingXPos = 0;

    // Dynamically generate tiles for background based on # of columns and rows
    for (int column = 0; column < NUM_OF_BACKGROUND_TILE_COLUMNS; column++)
    {
        // Start background tile positioning at the top of the window.
        // Each new column of tiles added will reset back to top of window.
        float startingYPos = 0;
        for (int row = 0; row < NUM_OF_BACKGROUND_TILE_ROWS; row++)
        {
            sf::Sprite* background = new sf::Sprite(SPRITE_TILE_GRASS_01_TEXTURE);
            background->setScale(BACKGROUND_TILE_SCALE);
            background->setPosition(sf::Vector2f{startingXPos, startingYPos});
            backgroundSprites.push_back(*background);

            // Modify Y for next row entry
            startingYPos += (TILE_SIZE * BACKGROUND_TILE_SCALE.y);
        }

        // Modify X for next column entry
        startingXPos += (TILE_SIZE * BACKGROUND_TILE_SCALE.x);
    }

    /**
     * SPAWN PLAYER AT CENTER
     */
    sf::Sprite* player = new sf::Sprite(SPRITE_PLAYER_TEXTURE);
	player->setScale(sf::Vector2f{2, 2});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	player->setOrigin(player->getLocalBounds().getCenter());
	player->setPosition(sf::Vector2f{WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f});
    // Save pointer later to do more with the button (like hover detection)
    this->player = player;
}

void Game::updateDll()
{
    const std::filesystem::path dllPath = "game_logic.dll";

    if (!std::filesystem::exists(dllPath))
    {
        return;
    }

    const auto now = std::filesystem::last_write_time(dllPath);

    // @todo Fix later
    // if (!dllHandle)
    // {
    //     dllHandle = LoadLibraryA(dllPath.string().c_str());
    //     if (!dllHandle)
    //     {
    //         std::cout << "Failed to load game_logic.dll\n";
    //         return;
    //     }

    //     dllSetTitle = reinterpret_cast<SetTitleFn>(
    //         GetProcAddress(static_cast<HMODULE>(dllHandle), "hot_reload_set_title"));

    //     if (!dllSetTitle)
    //     {
    //         std::cout << "DLL missing hot_reload_set_title export\n";
    //         FreeLibrary(static_cast<HMODULE>(dllHandle));
    //         dllHandle = nullptr;
    //         return;
    //     }

    //     dllLastWrite = now;
    // }

    // if (now != dllLastWrite)
    // {
    //     std::cout << "Reloading DLL...\n";
    //     const auto oldHandle = dllHandle;
    //     dllHandle = nullptr;
    //     dllSetTitle = nullptr;
    //     FreeLibrary(static_cast<HMODULE>(oldHandle));

        
    //     dllHandle = dlopen(dllPath.string().c_str(), RTLD_LAZY);
    //     if (!dllHandle) return;
    //     dllSetTitle = reinterpret_cast<SetTitleFn>(
    //         dlsym(dllHandle, "hot_reload_set_title"));

    //     dllSetTitle = reinterpret_cast<SetTitleFn>(
    //         GetProcAddress(static_cast<HMODULE>(dllHandle), "hot_reload_set_title"));

    //     if (!dllSetTitle)
    //     {
    //         std::cout << "DLL missing hot_reload_set_title export after reload\n";
    //         FreeLibrary(static_cast<HMODULE>(dllHandle));
    //         dllHandle = nullptr;
    //         return;
    //     }

    //     dllLastWrite = now;
    // }

    // if (dllSetTitle)
    // {
    //     for (auto* element : mainMenuElements)
    //     {
    //         if (auto* text = dynamic_cast<sf::Text*>(element))
    //         {
    //             dllSetTitle(*text, "DLL Hot Reload Title");
    //             break;
    //         }
    //     }
    // }
}

void Game::update()
{
    updateDll();
    updateInput();
    updateGUI();
    updatePollEvents();
    if (currentState == GameState::Playing)
    {
        updateWorld();
    }

    // 4. Hover Detection Logic
    // Get the current local mouse position relative to the active window
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    // Convert window pixel coordinates to world/view coordinates
    sf::Vector2f mousePosF = window->mapPixelToCoords(mousePos);

    // Check if mouse is bounds of the button shape
    if (playButton->getGlobalBounds().contains(mousePosF))
    {
        playButton->setColor(BUTTON_HOVER_COLOR);
    } 
    else
    {
        // Set back to normal colors
        playButton->setColor(sf::Color::White);
    }
}

void Game::updatePollEvents()
{
	// Process events
    while (const std::optional event = window->pollEvent())
    {
        // Close window: exit
        if (event->is<sf::Event::Closed>())
            window->close();
    }
}

void Game::updateGUI()
{
    if (currentState == GameState::MainMenu)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            // Get current mouse positions relative to the window
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            // Convert integer window mouse positions to floating-point coordinates
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        
            // Check if mouse click hits the button boundaries
            if (playButton->getGlobalBounds().contains(mousePosF)) {
                std::cout << "Button Clicked! Performing action..." << std::endl;
                currentState = GameState::Playing;
                // @todo Don't want to reinitialize the world every time we click the button. Only do this once when transitioning to Playing state.
                initWorld(); // Initialize the world when transitioning to Playing state
            }
        }
    }
}

void Game::updateInput()
{
    std::cout << player->getPosition().x << ", " << player->getPosition().y << std::endl;
    if (currentState == GameState::Playing)
    {
        // Player Inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            player->move(sf::Vector2f(-1, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            player->move(sf::Vector2f(1, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            player->move(sf::Vector2f(0, -1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            player->move(sf::Vector2f(0, 1));
    }
}

void Game::updateWorld()
{
    
}

void Game::render()
{
    std::cout << "Current Game State: " << (currentState == GameState::MainMenu ? "Main Menu" : "Playing") << std::endl;
    window->clear(sf::Color(30, 30, 30)); // Dark background
	switch (currentState) {
        case GameState::MainMenu:
            for (const auto& element : mainMenuElements) {
                window->draw(*element);
            }
            break;

        case GameState::Playing:
            for (const auto& element : backgroundSprites) {
                window->draw(element);
            }
            window->draw(*player);
            break;
    }

    window->display();
}