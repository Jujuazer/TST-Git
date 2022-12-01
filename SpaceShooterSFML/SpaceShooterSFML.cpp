#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "ChronoSpacer");
	// Initialise everything below
	ConvexShape spaceship1;
	spaceship1.setPointCount(3);
	spaceship1.setPoint(0, Vector2f(0, -75));
	spaceship1.setPoint(1, Vector2f(-25, 25));
	spaceship1.setPoint(2, Vector2f(25, 25));
	spaceship1.setPosition(Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f });

	ConvexShape spaceship2;
	spaceship2.setPointCount(3);
	spaceship2.setPoint(0, Vector2f(0, -20));
	spaceship2.setPoint(1, Vector2f(-60, 10));
	spaceship2.setPoint(2, Vector2f(60, 10));
	spaceship2.setFillColor(Color(200, 200, 200));
	spaceship2.setPosition(Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 });

	ConvexShape spaceship3;
	spaceship3.setPointCount(3);
	spaceship3.setPoint(0, Vector2f(0, 20));
	spaceship3.setPoint(1, Vector2f(-50, -5));
	spaceship3.setPoint(2, Vector2f(50, -5));
	spaceship3.setFillColor(Color(150, 150, 150));
	spaceship3.setPosition(Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 });
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
		window.draw(spaceship3);
		window.draw(spaceship2);
		window.draw(spaceship1);
		// Whatever I want to draw goes here
		window.display();
	}
}