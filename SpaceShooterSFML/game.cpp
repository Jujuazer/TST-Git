#define _USE_MATH_DEFINES
#include <iostream>
#include "game.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "Enemy.h"
#include <random>

float randomEnemySpeed() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(300.0f, 600.0f);
	return dist(mt);
}

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

void drawEnemy(Game& game, RenderWindow& window) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		window.draw((*it).shape2);
		window.draw((*it).shape);
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
	
