#include "Assets.hpp"
#include "Main.hpp"
#include "Game.hpp"
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

void Game::updatePollEvents()
{
	while ( const std::optional event = window->pollEvent() )
    {
		if ( event->is<sf::Event::Closed>() )
     	    window->close();
		// if (event->is<sf::Event::KeyPressed>() && event->get<sf::Event::KeyPressed>().code == sf::Keyboard::Escape)
		// 	this->window->close();
	}
}

void Game::update()
{
    updatePollEvents();

    // 4. Hover Detection Logic
    // Get the current local mouse position relative to the active window
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    // Convert window pixel coordinates to world/view coordinates
    sf::Vector2f mousePosF = window->mapPixelToCoords(mousePos);

    // Check if mouse is bounds of the button shape
    if (playButton->getGlobalBounds().contains(mousePosF)) {
        playButton->setColor(BUTTON_HOVER_COLOR);
    } else {
        // Set back to normal colors
        playButton->setColor(sf::Color::White);
    }
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
            // Only draw actual gameplay items when playing
            // window.draw(playerSp);
            // window.draw(mapSp);
            break;
    }

    window->display();
}