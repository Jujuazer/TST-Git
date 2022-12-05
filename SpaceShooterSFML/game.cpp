#define _USE_MATH_DEFINES
#include <iostream>
#include "game.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>

void MoveBullets(Game& game, float deltaTime) {

	for (std::list<Bullet>::iterator it = game.Bullets.begin(); it != game.Bullets.end(); it++) {
		float deltaX = (*it).speed * (*it).direction.x * deltaTime;
		float deltaY = (*it).speed * (*it).direction.y * deltaTime;
		(*it).position.x += deltaX;
		(*it).position.y += deltaY;

		(*it).bulletForm.setPosition((*it).position);
	}
	//set position form
}

void DrawBullets(Game& game, RenderWindow& window) {
	for (std::list<Bullet>::iterator it = game.Bullets.begin(); it != game.Bullets.end(); it++) {
		window.draw((*it).bulletForm);
	}
}

void SlowDown(Game& game, float& deltaTime, float divideValue) {
	deltaTime = game.originalDeltaTime/ divideValue;
}

void ResetDeltaTime(Game& game, float& deltaTime) {
	deltaTime = game.originalDeltaTime;
}

void HandleKeyInput(Vector2f& direction) {
	//multiple inputs
	if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
		direction.y = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		direction.y = 1;
	}
	else {
		direction.y = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		direction.x = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		direction.x = 1;
	}
	else {
		direction.x = 0;
	}
}