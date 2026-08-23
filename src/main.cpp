#include "Game.hpp"

int main()
{
	Game Game;

	sf::Clock deltaClock;

	// Game loop
	while ( Game.isOpen() )
	{
		float dt = deltaClock.restart().asSeconds();

		Game.update(dt);
		Game.render();
	}

	//End of application
	return 0;
}
