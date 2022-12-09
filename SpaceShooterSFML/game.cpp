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

float randomEnemyShootDelay2() {
	//random float between 2 and 5
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.5f, 2.0f);
	return dist(mt);
}

float randomEnemyDirection() {
	// random float between -10 and 10
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
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

void DrawEnemyBullets(Game& game, RenderWindow& window) {
	for (std::list<EnemyBullet>::iterator it = game.EnemyBullets.begin(); it != game.EnemyBullets.end(); it++) {
		window.draw((*it).shape);
	}
}

void drawEnemy(Game& game, RenderWindow& window) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		window.draw((*it).shape2);
		window.draw((*it).shape);
	}
}


void generateEnemy(Score& Gscore, Game& game, RenderWindow& window, Vector2f direction) {
	int x;
	int y = 0;
	int* py = &y;
	int z = 5;
	int* pz = &z;
	
	if (y < 15) {
		y = 5 * (Gscore.score / 300);
	}
	if (z < 50) {
		z = 5 * (Gscore.score / 150);
	}

	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0 + y, 5 + z);
	int a = dis(gen);

	//each time score increase by 300, y increase by 5
	y = 5 * (Gscore.score / 300);
	
	if (Gscore.score < 300) {
		x = 50;
	}
	else if (Gscore.score < 600) {
		x = 40;
	}
	else if (Gscore.score >= 600) {
		x = 30;
	}

	

	if (Gscore.score % x == 0 && Gscore.score != 0) {
		for (int i = 0; i < a; i++) {
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
			(*it).direction.x = randomEnemyDirection();
			(*it).hasSpeed = true;

		}
	}
}

void EnemyShoot(Game& game, float deltaTime, RenderWindow& window) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		(*it).shootCounter += deltaTime;
		if ((*it).shootCounter >= (*it).shootDelay) {
			EnemyBullet bullet;
			setupEnemyBullet(bullet, window, (*it).direction, game, (*it).position);
			(*it).shootCounter = 0.0f;
			(*it).shootCounter = 0.0f;
			(*it).shootDelay = randomEnemyShootDelay2();
		}
	}
}

void updateEnemyBullets(Game& game, float deltaTime) {
	for (std::list<EnemyBullet>::iterator it = game.EnemyBullets.begin(); it != game.EnemyBullets.end(); it++) {
		float deltaX = (*it).speed * (*it).direction.x * deltaTime;
		float deltaY = (*it).speed * (*it).direction.y * deltaTime;
		(*it).position.y += deltaY;

		(*it).shape.setPosition((*it).position);
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
