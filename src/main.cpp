#include "Game.hpp"
#include "HotReloadSystem.hpp"

#include <dlfcn.h> // Core header for POSIX dynamic loading (.so)

int main()
{
	Game Game;

	sf::Clock deltaClock;


	// Hot Reloading logic
	// Open the compiled .so library

	// Test window
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Testing DLL Hot Reload");

	// Test text
	sf::Text text = sf::Text(GAME_TITLE_FONT);
	text.setCharacterSize(30);
	text.setPosition(sf::Vector2f(100.f, 250.f));
	text.setString("Initial default num: 0");

	HotReloadSystem reloadSystem;
    
    // Initial explicit load pass on execution startup
    try_hot_reload(reloadSystem);

	// Game loop
	while ( Game.isOpen() )
	{
		float dt = deltaClock.restart().asSeconds();

		// Main Game
		Game.update(dt);
		Game.render();


		// 1. Scan filesystem for changes every frame
        try_hot_reload(reloadSystem);

		// 2. Safely call your update function if the pointer is currently initialized
        if (reloadSystem.hot_reload_get_num) {
            // Note: In real scenarios, you can change this dynamic text variable inside GameDll.cpp on the fly!
            int num = reloadSystem.hot_reload_get_num();
			text.setString("Initial default num: " + std::to_string(num));
        }

		window.clear(sf::Color(25, 25, 30));
        window.draw(text);
        window.display();
	}

	// Clean up library mappings when exiting the application cleanly
    if (reloadSystem.handle) {
        dlclose(reloadSystem.handle);
    }

	//End of application
	return 0;
}
