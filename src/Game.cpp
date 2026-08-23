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
    // Just initialize the pause menu, but don't load it yet.
    initPauseMenu();
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

void Game::initPauseMenu()
{
    sf::Text* pauseMenuText = new sf::Text(GAME_TITLE_FONT, sf::String("PAUSE MENU PLACEHOLDER"), 50);
    pauseMenuText->setFillColor(sf::Color::White);
    // @todo Is this really necessary? It seems to be a workaround for a bug in SFML 2.5.1 where the text's origin is not set correctly when using a custom font.
	// Center the title's origin to allow easy horizontal alignment
	pauseMenuText->setOrigin(pauseMenuText->getLocalBounds().getCenter());

	// Position: Horizontal center, 80 pixels down from the top edge
	pauseMenuText->setPosition(sf::Vector2f{WINDOW_WIDTH / 2.0f, 80.0f});
    pauseMenuElements.push_back(pauseMenuText);
    this->pauseMenuText = pauseMenuText;
}

void Game::updatePauseMenu()
{
    pauseMenuText->setPosition(playerCamera->getCenter());
}

void Game::initWorld()
{
    /**
     * GENERATE BACKGROUND TILES
     */
    // Start background tile positioning at 1-tile beyond the left-side of the window
    float startingXPos = -TILE_SIZE;

    // Dynamically generate tiles for background based on # of columns and rows
    for (int column = 0; column < NUM_OF_BACKGROUND_TILE_COLUMNS; column++)
    {
        // Start background tile positioning at 1-tile beyond the top of the window.
        // Each new column of tiles added will reset back to top of window.
        float startingYPos = -TILE_SIZE;
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
    // Save pointer later to do more with the sprite
    AnimatedSprite* player = new AnimatedSprite(SPRITE_PLAYER_TEXTURE, 13);
	player->setScale(sf::Vector2f{2, 2});
	// Re-adjust the origin to the center of the sprite for proper positioning after scaling up
	player->setOrigin(player->getLocalBounds().getCenter());
	player->setPosition(sf::Vector2f{WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f});
    this->player = player;
    this->playerCamera = new sf::View(sf::FloatRect({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
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

void Game::update(float dt)
{
    updateDll();
    updateGUI();
    updateInput();
    updatePauseMenu();
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

    player->update();
}

/**
 * @brief Continuously polls for SFML events. Events captured here are executed once,
 * then deleted from the internal queue.
 */
void Game::updatePollEvents()
{
	// Process events
    while (const std::optional event = window->pollEvent())
    {
        // Close window: exit
        if (event->is<sf::Event::Closed>())
        {
            window->close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape) 
            {
                if (currentState == GameState::Playing)
                {
                    currentState = GameState::Paused;
                }
                else if (currentState == GameState::Paused)
                {
                    currentState = GameState::Playing;
                }
            }
        }
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
    float activeXMovement = 0.f;
    float activeYMovement = 0.f;
    if (currentState == GameState::Playing)
    {
        // Player Inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player->setScale(sf::Vector2f(-2, 2)); // Flip horizontally to face left
            activeXMovement = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player->setScale(sf::Vector2f(2, 2)); // Reset to original right-facing position
            activeXMovement = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            activeYMovement = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            activeYMovement = 1.f;
        }

        if ((activeXMovement != 0) || (activeYMovement != 0))
        {
            player->setState(AnimationState::MOVING);
            // If we have both x and y movements, normalize the speed so we don't go faster when combining the movements
            if ((activeXMovement != 0) && (activeYMovement != 0))
            {
                // True vector normalization
                float magnitude = std::sqrt((activeXMovement * activeXMovement) + (activeYMovement * activeYMovement));
                if (magnitude > 0.0f)
                {
                    activeXMovement /= magnitude;
                    activeYMovement /= magnitude;
                }
            }

            player->move(sf::Vector2f(activeXMovement, activeYMovement));
        }
        else
        {
            player->setState(AnimationState::IDLE);
        }

        playerCamera->setCenter(player->getPosition());
    }
}

/**
 * Updates background sprite tiles to create an infinite background loop. Whenever
 * tiles are no longer on screen, use a conveyor-belt like system that wraps them
 * back around to be back in view of player camera. 
 */
void Game::updateBackground()
{
    if (!playerCamera)
    {
        return;
    }

    const sf::Vector2f cameraCenter = playerCamera->getCenter();
    const sf::Vector2f cameraHalfSize = playerCamera->getSize() * 0.5f;
    const float tileWidth = TILE_SIZE * BACKGROUND_TILE_SCALE.x;
    const float tileHeight = TILE_SIZE * BACKGROUND_TILE_SCALE.y;
    const float gridWidth = NUM_OF_BACKGROUND_TILE_COLUMNS * tileWidth;
    const float gridHeight = NUM_OF_BACKGROUND_TILE_ROWS * tileHeight;

    const float cameraLeft = cameraCenter.x - cameraHalfSize.x;
    const float cameraRight = cameraCenter.x + cameraHalfSize.x;
    const float cameraTop = cameraCenter.y - cameraHalfSize.y;
    const float cameraBottom = cameraCenter.y + cameraHalfSize.y;

    for (auto& tile : backgroundSprites)
    {
        sf::Vector2f tilePosition = tile.getPosition();
        const sf::FloatRect tileBounds = tile.getGlobalBounds();

        const float tileLeft = tilePosition.x;
        const float tileRight = tilePosition.x + tileBounds.size.x;
        const float tileTop = tilePosition.y;
        const float tileBottom = tilePosition.y + tileBounds.size.y;

        if (tileRight < cameraLeft)
        {
            tilePosition.x += gridWidth;
        }
        else if (tileLeft > cameraRight)
        {
            tilePosition.x -= gridWidth;
        }

        if (tileBottom < cameraTop)
        {
            tilePosition.y += gridHeight;
        }
        else if (tileTop > cameraBottom)
        {
            tilePosition.y -= gridHeight;
        }

        tile.setPosition(tilePosition);
    }
}

void Game::updateWorld()
{
    updateBackground();
}

void Game::renderPlaying()
{
    // Apply your custom camera view before drawing world objects
    window->setView(*playerCamera);
    for (const auto& element : backgroundSprites) {
        window->draw(element);
    }
    window->draw(*player);
}

void Game::render()
{
    window->clear(sf::Color(30, 30, 30)); // Dark background
	switch (currentState) {
        case GameState::MainMenu:
            for (const auto& element : mainMenuElements) {
                window->draw(*element);
            }
            break;

        case GameState::Playing:
            renderPlaying();
            break;

        case GameState::Paused:
            // Continue to render anything in the Playing state (world, player, etc.)
            renderPlaying();
            // Render PauseMenu elements over the current game state
            for (const auto& element : pauseMenuElements) {
                window->draw(*element);
            }
            break;
    }

    window->display();
}