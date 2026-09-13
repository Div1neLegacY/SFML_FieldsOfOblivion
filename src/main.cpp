#include "Game.hpp"

#include <dlfcn.h> // Core header for POSIX dynamic loading (.so)

int main()
{
	Game Game;

	sf::Clock deltaClock;
	float dt; // Define dt here at the top level

	// Test text
	sf::Text text = sf::Text(GAME_FONT);
	text.setCharacterSize(30);
	text.setPosition(sf::Vector2f(100.f, 250.f));
	text.setString("Initial default num: 0");

	// Game loop
	while ( Game.isOpen() )
	{
		dt = deltaClock.restart().asSeconds();

		// Main Game
		Game.update(dt);
		Game.render();
	}

	//End of application
	return 0;
}
