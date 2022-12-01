#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "TST");
	// Initialise everything below
	ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0,Vector2f(0,-75));
	convex.setPoint(1,Vector2f(-25,25));
	convex.setPoint(2,Vector2f(25,25));
	convex.setPosition(Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f });
	ConvexShape convex2;
	convex2.setPointCount(3);
	convex2.setPoint(0,Vector2f(0,-20));
	convex2.setPoint(1,Vector2f(-50,10));
	convex2.setPoint(2,Vector2f(50,10));
	convex2.setPosition(Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 });
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
		window.draw(convex2);
		// Whatever I want to draw goes here
		window.display();
	}
}