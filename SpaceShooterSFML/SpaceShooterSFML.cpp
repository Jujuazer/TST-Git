#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "speed.h";
#include "Score.h";
#include "UI.h";
#include "math.h";
#include "game.h";

int main()
{
	RenderWindow window(sf::VideoMode(1920, 1080), "Through Space And Time");
	// Initialise everything below

	Clock mainClock;

	Game game;

	SpaceShip spaceShip;
	setupSpaceShip(spaceShip, Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 }, Vector2f{ 1,1 });

	Score gameScore;
	SetUpScore(gameScore, 0.1f); // time between each score increase

	Vector2f direction{ 0, 0 };

	ConvexShape square;
	SetShape(square, 0, 1080, 0, 460, Color(30, 30, 30, 255));
	ConvexShape square2;
	SetShape(square2, 0, 1080, 1460, 1920, Color(30, 30, 30, 255));

	GameOver gameoverScreen;
	gameoverScreen.score = &gameScore;
	SetGameOver(gameoverScreen, window);

	GAMESTATE gameState = GAMESTATE::PLAYING;

	// Game loop
	while (window.isOpen()) {
		Event event;
		Time time = mainClock.restart();


		float deltaTime = time.asSeconds();



		RetryButtonF(gameoverScreen, window);


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

			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Key::Space)) {
				Shoot(spaceShip, game, direction);
			}

			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Key::M)) {
				DisplayGameOver(gameoverScreen, gameState); // Sets the game to the Game Over menu
			}

			rotateShip(spaceShip, direction);

			//std::cout << "x : " << direction.x << " y : " << direction.y << std::endl;

		}

		PlayStageCollision(spaceShip, window, direction);
		normalizeVector(direction);
		move(spaceShip, direction, deltaTime);
		MoveBullets(game, deltaTime);
		AddPerTime(gameScore, deltaTime, 1);

		//std::cout << spaceShip.position.x << std::endl;



		// Clear the window to black
		window.clear();

		// Whatever I want to draw goes here

		if (gameState == GAMESTATE::PLAYING)
		{
		updateDrawSpaceShip(spaceShip, window);
		window.draw(square);
		window.draw(square2);
		UpdateDrawScore(gameScore, window);
		DrawBullets(game, window);
		}
		else if (gameState == 1)
		{
		DrawGameOver(gameoverScreen, window, deltaTime);
		}
		//display the new window frame
		window.display();
	}
}