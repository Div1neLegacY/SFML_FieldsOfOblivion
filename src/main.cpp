#include "Game.hpp"

int main()
{
	Game Game;

	// Game loop
	while ( Game.isOpen() )
	{
		Game.update();
		Game.render();
	}

	//End of application
	return 0;
}
