#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "speed.h";
#include "Score.h";
#include "UI.h";
#include "math.h";
#include "game.h";
#include "ParticleSystem.h"

int main()
{
	RenderWindow window(sf::VideoMode(1920, 1080), "ChronoSpacer");
	// Initialise everything below

	Clock mainClock;

	Game game;

	ParticleSystem particleSystem = CreateParticleSystem(0.2f, 2, 3, {0,0}, 4, 2);

	SpaceShip spaceShip;                                                                     //space ship size // shoot delay
	setupSpaceShip(spaceShip, Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 }, 0.7f        , 0.1f);
	
	Score gameScore;
	SetUpScore(gameScore, 0.1f); // time between each score increase

	Vector2f direction{ 0, 0 };

	ConvexShape square;
	SetShape(square, 0, 1080, 0, 460);
	ConvexShape square2;
	SetShape(square2, 0, 1080, 1460, 1920);

	window.setKeyRepeatEnabled(false);


	// Game loop
	while (window.isOpen()) {
		Event event;
		Time time = mainClock.restart();
		float deltaTime = time.asSeconds();
		game.originalDeltaTime = deltaTime;

		HandleKeyInput(direction);

		//if no keys are pressed (moving keys) it slowdow
		if (!Keyboard::isKeyPressed(Keyboard::Key::D) && !Keyboard::isKeyPressed(Keyboard::Key::S) && !Keyboard::isKeyPressed(Keyboard::Key::Z) && !Keyboard::isKeyPressed(Keyboard::Key::Q)) {
			spaceShip.isMoving = false;
		}
		else if (Keyboard::isKeyPressed) {
			spaceShip.isMoving = true;
		}


		// one single input
		while (window.pollEvent(event)) {

			// Process any input event here
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Key::Space) && spaceShip.shootOpen) {
				Shoot(spaceShip, game, direction);
				spaceShip.shootOpen = false;
				spaceShip.shootCounter = 0;
			}

			rotateShip(spaceShip, direction);

			//std::cout << "x : " << direction.x << " y : " << direction.y << std::endl;
		}

		//std::cout << "is moving : " << spaceShip.isMoving << " deltaTime : " << deltaTime << std::endl;
		//SlowDown mechanic while not moving
		if (!spaceShip.isMoving) {
			SlowDown(game, deltaTime, 10);
		}

		if (!spaceShip.shootOpen) {

			if (spaceShip.shootCounter > spaceShip.shootDelay) {
				spaceShip.shootOpen = true;
			}
			spaceShip.shootCounter += deltaTime;
		}

		PlayStageCollision(spaceShip, window, direction);
		normalizeVector(direction);
		move(spaceShip, direction, deltaTime);
		MoveBullets(game, deltaTime);
		AddPerTime(gameScore, deltaTime, 1);
		UpdateParticleSystem(particleSystem, deltaTime);

		//std::cout << spaceShip.position.x << std::endl;
		

		
		// Clear the window to black
		window.clear();

		// Whatever I want to draw goes here
		updateDrawSpaceShip(spaceShip, window);
		window.draw(square);
		window.draw(square2);
		UpdateDrawScore(gameScore, window);
		DrawBullets(game, window);
		DrawParticleSystem(particleSystem, window);
		
		//display the new window frame
		window.display();
	}
}    