#define _USE_MATH_DEFINES
#include <iostream>
#include "game.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "Enemy.h"
#include <random>
#include "math.h"
#include "UI.h"
struct SpaceShip;

const float xOffsetBox = 20;
const float yOffsetBox = 20;

float randomEnemySpeed() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(300.0f, 600.0f);
	return dist(mt);
}

void CheckBulletCollision(Game& game) {
	bool isBreak = false;
	for (std::list<Bullet>::iterator it = game.Bullets.begin(); it != game.Bullets.end(); it++) {
		for (std::list<Enemy>::iterator it2 = game.Enemies.begin(); it2 != game.Enemies.end(); it2++) {

			if (IsOverlappingBoxOnBox((*it).boxCollider.getPosition(), (*it).boxCollider.getSize(), (*it2).boxCollider.getPosition(), (*it2).boxCollider.getSize())) {
				it2 = game.Enemies.erase(it2);
				it = game.Bullets.erase(it);
				isBreak = true;
				break;
			}
		}
		if (isBreak) {
			break;
			isBreak = false;
		}
	}
}

void MoveBullets(Game& game, float deltaTime) {

	for (std::list<Bullet>::iterator it = game.Bullets.begin(); it != game.Bullets.end(); it++) {
		float deltaX = (*it).speed * (*it).direction.x * deltaTime;
		float deltaY = (*it).speed * (*it).direction.y * deltaTime;
		(*it).position.x += deltaX;
		(*it).position.y += deltaY;

		(*it).bulletForm.setPosition((*it).position);
		(*it).boxCollider.setPosition({ (*it).position.x - xOffsetBox, (*it).position.y - yOffsetBox});
	}
}

void DrawBullets(Game& game, RenderWindow& window) {
	for (std::list<Bullet>::iterator it = game.Bullets.begin(); it != game.Bullets.end(); it++) {
		window.draw((*it).bulletForm);
		//window.draw((*it).boxCollider);
	}
}

void drawEnemy(Game& game, RenderWindow& window) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		window.draw((*it).shape2);
		window.draw((*it).shape);
		//window.draw((*it).boxCollider);
	}
}

void moveEnemy(Game& game, float deltaTime) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		float deltaX = (*it).speed * (*it).direction.x * deltaTime;
		float deltaY = (*it).speed * (*it).direction.y * deltaTime;
		(*it).position.x -= deltaX;
		(*it).position.y -= deltaY;
		(*it).shape.setPosition((*it).position);
	}
}

void generateEnemy(Score& Gscore, Game& game, RenderWindow& window, Vector2f direction) {
	int x;
	int y;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 5);
	int a = dis(gen);

	if (Gscore.score < 300) {
		x = 50;
		y = 1;
	}
	else if (Gscore.score < 600) {
		x = 40;
		y = 3;
	}
	else if (Gscore.score >= 600) {
		x = 30;
		y = 5;
	}
	if (Gscore.score % x == 0 && Gscore.score != 0) {
		for (int i = 0; i < y + a; i++) {
			Enemy enemy;
			setupEnemy(enemy, window, direction, game);
		}
		Gscore.score += 1;
	}
}

void ChangeEnemySpeed(Game& game, float deltaTime) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		(*it).speedCounter += deltaTime;
		if ((*it).speedCounter >= (*it).speedDelay && (*it).hasSpeed == false) {
			(*it).speed = randomEnemySpeed();
			(*it).hasSpeed = true;

		}
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
