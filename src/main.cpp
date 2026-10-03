#include "Game.hpp"
#include "Utilities.hpp"

#include <dlfcn.h> // Core header for POSIX dynamic loading (.so)

std::minstd_rand WEAPON_UPGRADE_GENERATOR{std::random_device{}()};

int main()
{
	Game Game;

	sf::Clock deltaClock;
	float dt; // Define dt here at the top level

	// @TODO This is just a test to see if the weighted random selection is working correctly. Remove this later.
	for (int i = 0; i < 3; ++i)
	{
		BaseWeapon randomWeapon = weightedRandomSelection(WEAPON_UPGRADE_GENERATOR, WEAPON_UPGRADE_TABLE);
		printf("Randomly selected weapon: %s\n", randomWeapon.stats.weapon.toAnsiString().c_str());
	}

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
