#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "speed.h";



int main()
{
	RenderWindow window(sf::VideoMode(1920, 1080), "ChronoSpacer");
	// Initialise everything below

	Clock mainClock;

	SpaceShip spaceShip;
	setupSpaceShip(spaceShip, Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 }, Vector2f{1,1});
	Vector2f direction{ 0, 0 };
	

	// Game loop
	while (window.isOpen()) {
		Event event;
		Time time = mainClock.restart();
		float deltaTime = time.asSeconds();

		while (window.pollEvent(event)) {

			// Process any input event here
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Z) {
				direction.y = -1;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::S) {
				direction.y = 1;
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Q) {
				direction.x = -1;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::D) {
				direction.x = 1;
			}

			if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Key::D || event.key.code == Keyboard::Key::Q)) {
				direction.x = 0;
			}

			if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Key::Z || event.key.code == Keyboard::Key::S)) {
				direction.y = 0;
			}

			rotateShip(spaceShip, direction);

			//std::cout << "x : " << direction.x << " y : " << direction.y << std::endl;

		}

		PlayStageCollision(spaceShip, window, direction);
		normalizeVector(direction);
		move(spaceShip, direction, deltaTime);

		std::cout << spaceShip.position.x << std::endl;
		

		
		// Clear the window to black
		window.clear();

		// Whatever I want to draw goes here
		updateDrawSpaceShip(spaceShip, window);
		
		//display the new window frame
		window.display();
	}
}    