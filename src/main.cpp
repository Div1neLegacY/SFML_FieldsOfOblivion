#include "Game.hpp"

#include <dlfcn.h> // Core header for POSIX dynamic loading (.so)

int main()
{
	Game Game;

	sf::Clock deltaClock;
	float dt; // Define dt here at the top level

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
