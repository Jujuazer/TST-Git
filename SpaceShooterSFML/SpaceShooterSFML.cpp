#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "ChronoSpacer");
	// Initialise everything below
	ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0,Vector2f(0,0));
	convex.setPoint(1,Vector2f(0,50));
	convex.setPoint(2,Vector2f(50,50));
	convex.setPosition(Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f });
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
		window.draw(convex);
		// Whatever I want to draw goes here
		window.display();
	}
}