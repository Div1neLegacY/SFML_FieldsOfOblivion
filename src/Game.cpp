#include "Assets.hpp"
#include "Main.hpp"
#include "Game.hpp"
#include "Utilities.hpp"
#include <filesystem>
#include <iostream>
#include <algorithm>


Game::Game()
{
    window = new sf::RenderWindow( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Fields of Oblivion" );
    window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
    player = new Player();

    for (int i = 0; i < 30; i++)
    {
        auto enemy_ptr = std::make_unique<Enemy>(i);
        enemy_ptr->setPosition(sf::Vector2f{i * 50.0f, 0});
        enemies.push_back(std::move(enemy_ptr));
    }

    initMainMenu();
    // Just initialize the pause menu, but don't load it yet.
    initPauseMenu();
}

Game::~Game()
{
    delete window, player, expBar, healthBar;
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
    sf::Text* title = new sf::Text(GAME_FONT, GAME_TITLE, 50);
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
	playButton->setPosition(WINDOW_CENTER);
    // Save pointer later to do more with the button (like hover detection)
    this->playButton = playButton;

    mainMenuElements.push_back(title);
    mainMenuElements.push_back(playButton);
    std::cout << "Main Menu Initialized." << std::endl;
}

void Game::initPauseMenu()
{
    sf::Text* pauseMenuText = new sf::Text(GAME_FONT, sf::String("PAUSE MENU PLACEHOLDER"), 50);
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
    pauseMenuText->setPosition(player->camera->getCenter());
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

    // @todo: Remove when transferred to HealthBar class
    // Health bar, currently not attached to player
    auto* healthBar = new sf::RectangleShape(sf::Vector2f(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT));
    healthBar->setFillColor(sf::Color::Green);
    // Center on screen by moving to middle, than adjusting based on size
    healthBar->setPosition(WINDOW_CENTER);
    healthBar->move(sf::Vector2f{-(HEALTH_BAR_WIDTH / 2), -(HEALTH_BAR_HEIGHT / 2)});
    // Additionally move down below player
    healthBar->move(sf::Vector2f{0, 30.f});
    healthBar->setOutlineThickness(1.0f);
    healthBar->setOutlineColor(sf::Color::White);
    this->healthBar = healthBar;
    playingUIElements.push_back(healthBar);

    this->expBar = new ExpBar(300.f, 20.f);
}

void Game::update(float dt)
{
    updateGUI();
    updateInput();
    updatePauseMenu();
    updatePollEvents();
    if (currentState == GameState::Playing)
    {
        updateWorld(dt);
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

    player->update(dt);

    //@TODO: Move this into a better method rather than checking for each orb
    for (size_t i = 0; i < expOrbs.size(); ++i)
    {
        if (checkCollision(player, expOrbs[i].get()))
        {
            // Player has collected the orb
            expOrbs.erase(expOrbs.begin() + i);
            player->addExp(1);
            expBar->update(player->currentExp, player->currentLevelBracket->second, player->currentPlayerLevel);
        }
    }
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
            if (keyPressed->code == KB_TOGGLE_PAUSE) 
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
        if (sf::Keyboard::isKeyPressed(KB_MOVE_LEFT))
        {
            player->setScale(sf::Vector2f(-2, 2)); // Flip horizontally to face left
            // @todo HARDCODED: Fix later, move into Player class
            if (player->attackAnimationSprite && !player->attackAnimationSprite->isActive())
            {
                // @todo Needs to match player direction, but currently doesn't. Need to fix this later.
                player->attackAnimationSprite->setScale(sf::Vector2f(-4, 2)); // Flip horizontally to face left
            }
            activeXMovement = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(KB_MOVE_RIGHT))
        {
            player->setScale(sf::Vector2f(2, 2)); // Reset to original right-facing position
            // @todo HARDCODED: Fix later, move into Player class
            if (player->attackAnimationSprite && !player->attackAnimationSprite->isActive())
            {
                // @todo Needs to match player direction, but currently doesn't. Need to fix this later.
                player->attackAnimationSprite->setScale(sf::Vector2f(4, 2)); // Flip horizontally to face left
            }
            activeXMovement = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(KB_MOVE_UP))
        {
            activeYMovement = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(KB_MOVE_DOWN))
        {
            activeYMovement = 1.f;
        }

        if ((activeXMovement != 0) || (activeYMovement != 0))
        {
            player->setState(AnimationState::ACTIVE);
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
            // Multiplier to adjust movement speed.
            float arbitrary_scale = 1.0f;
            player->move(sf::Vector2f(activeXMovement * arbitrary_scale, activeYMovement * arbitrary_scale));
        }
        else
        {
            player->setState(AnimationState::IDLE);
        }

        player->camera->setCenter(player->getPosition());
        //player->healthBar->update(100.f);
    }
}

/**
 * Updates background sprite tiles to create an infinite background loop. Whenever
 * tiles are no longer on screen, use a conveyor-belt like system that wraps them
 * back around to be back in view of player camera. 
 */
void Game::updateBackground()
{
    if (!player->camera)
    {
        return;
    }

    const sf::Vector2f cameraCenter = player->camera->getCenter();
    const sf::Vector2f cameraHalfSize = player->camera->getSize() * 0.5f;
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

void Game::updateEnemies(float dt)
{
    // 1. Tick down the invincibility timer using delta time
    if (invincibilityTimer > 0.0f)
    {
        invincibilityTimer -= dt;
    }

    size_t i = 0;
    while (i < enemies.size()) {
        enemies[i]->update(dt);

        // Move the enemy towards the player
        moveTowardsPlayer(dt, enemies[i].get(), player);

        // Check if enemy is overlapping player
        // Only damage the player if they are NOT currently invincible
        if (checkCollision(enemies[i].get(), player) && invincibilityTimer <= 0.0f)
        {
            int arbitraryNum = 10;
            currentHealth -= arbitraryNum;
            sf::Vector2 size = healthBar->getSize();
            size.x -= (HEALTH_BAR_WIDTH / arbitraryNum);
            size.x = std::max(size.x, 0.0f);
            healthBar->setSize(size);

            // Reset the timer to trigger the cooldown period
            invincibilityTimer = INVINCIBILITY_DURATION; 

            // Optional: Break out early so multiple overlapping enemies 
            // don't stack damage on the exact same frame
            break;
        }

        // Check if enemy was already hit during the current attack cycle
        if (player->attackAnimationSprite &&
            player->attackAnimationSprite->enemiesHitThisAttack.find(enemies[i].get()->getId()) == player->attackAnimationSprite->enemiesHitThisAttack.end())
        {
            // Check if enemy is overlapping player's attack
            if (checkCollision(enemies[i].get(), player->attackAnimationSprite.get()))
            {
                enemies[i].get()->damage(10); // Arbitrary damage value for now
                player->attackAnimationSprite->enemiesHitThisAttack.insert(enemies[i].get()->getId());
                if (enemies[i].get()->isDead())
                {
                    auto newExpOrb = std::make_unique<sf::Sprite>(SPRITE_EXP_ORB_SMALL_TEXTURE);
                    newExpOrb->setPosition(enemies[i]->getPosition());
                    expOrbs.push_back(std::move(newExpOrb));
                    enemies.erase(enemies.begin() + i);
                    continue;
                }
            }
        }

        i++;
    }


}

void Game::updateWorld(float dt)
{
    updateBackground();
    updateEnemies(dt);
}

void Game::renderPlaying()
{
    for (const auto& element : backgroundSprites) {
        window->draw(element);
    }

    window->draw(*player);
    window->draw(*player->attackAnimationSprite);

    renderEnemies();

    for (const auto& orb : expOrbs)
    {
        window->draw(*orb);
    }
}

void Game::renderEnemies()
{
    for (const auto& enemy : enemies)
    {
        // If enemy is in a damaged state, draw it with additive blending to force pixels to white
        if (enemy->isDamaged())
        {
            // Draw with additive blending to force pixels to white
            window->draw(*enemy, sf::BlendAdd);
            window->draw(*enemy, sf::BlendAdd);
        }
        else
        {
            window->draw(*enemy); // Draw normally
        }
    }
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

            // Switch to default view for static UI elements
            window->setView(window->getDefaultView());

            for (const auto& element : playingUIElements) {
                window->draw(*element);
            }

            expBar->draw(*window);

            // Apply your custom camera view before drawing world objects
            window->setView(*player->camera);

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