#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "ChronoSpacer");
	// Initialise everything below
	CircleShape triangle(80, 3);
	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		window.draw(triangle);
		// Whatever I want to draw goes here
		window.display();
	}
}