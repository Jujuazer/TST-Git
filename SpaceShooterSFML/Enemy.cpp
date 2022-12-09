#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <random>
#include "game.h"
#include "bullet.h"
using namespace sf;

float randomXposition() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(460, 1460);
	return dis(gen);
}

float randomSpeedDelay() {
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
	return r2;
}

float randomShootDelay() {
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
	return r2;
}

//random color
sf::Color randomColor() {
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	return sf::Color(r, g, b);
}


void setupEnemy(Enemy& enemy, RenderWindow& window, Vector2f direction, Game& game) {
	ConvexShape enemyTest;
	float a = randomXposition();

	
	enemyTest.setPointCount(7);
	
	enemyTest.setPoint(0, Vector2f(-10, 0));
	enemyTest.setPoint(1, Vector2f(10, 0));
	enemyTest.setPoint(2, Vector2f(30, 20));
	enemyTest.setPoint(3, Vector2f(10, 10));
	enemyTest.setPoint(4, Vector2f(0, 40));
	enemyTest.setPoint(5, Vector2f(-10, 10));
	enemyTest.setPoint(6, Vector2f(-30, 20));
	enemyTest.setPosition(Vector2f{ a ,-40.f});
	//random enemyTest fill color
	enemyTest.setFillColor(randomColor());
	
	
	enemyTest.setOutlineColor(Color::White);
	enemyTest.setOutlineThickness(1);

	ConvexShape enemyTest2;
	enemyTest2.setPointCount(6);
	enemyTest2.setPoint(0, Vector2f(-20, -5));
	enemyTest2.setPoint(1, Vector2f(0, 10));
	enemyTest2.setPoint(2, Vector2f(20, -5));
	enemyTest2.setPoint(3, Vector2f(25, 30));
	enemyTest2.setPoint(4, Vector2f(0, 0));
	enemyTest2.setPoint(5, Vector2f(-25, 30));
	enemyTest2.setFillColor(Color(100, 100, 100, 255));
	enemyTest2.setPosition(Vector2f{ a, -40.0f });
	
	

	
	enemy.shape = enemyTest;
	enemy.shape2 = enemyTest2;
	enemy.direction = direction;
	enemy.speed = 100.0f;
	enemy.position = Vector2f{ a , -40.f };
	enemy.shape.setPosition(enemy.position);
	enemy.shape2.setPosition(enemy.position);
	enemy.direction.x = 0.0f;
	enemy.direction.y = 1.0f;
	enemy.speedDelay =  randomSpeedDelay();
	enemy.shootDelay = 0.5f + randomShootDelay();
	
	
	//push enemy
	game.Enemies.push_back(enemy);
}




void updateEnemy(Game& game, float deltaTime) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		float deltaX = (*it).speed * (*it).direction.x * deltaTime;
		float deltaY = (*it).speed * (*it).direction.y * deltaTime;
		(*it).position.y += deltaY;
		(*it).position.x += deltaX;
		(*it).shape.setPosition((*it).position);
		(*it).shape2.setPosition((*it).position);

		

	} 
}
	
//setup EnemyBullet
void setupEnemyBullet(EnemyBullet& enemyBullet, RenderWindow& window, Vector2f direction, Game& game, Vector2f position) {
	ConvexShape enemyBulletTest;
	enemyBulletTest.setPointCount(3);
	enemyBulletTest.setPoint(0, Vector2f(-5, 0));
	enemyBulletTest.setPoint(1, Vector2f(5, 0));
	enemyBulletTest.setPoint(2, Vector2f(0, 20));
	enemyBulletTest.setFillColor(Color::Red);
	enemyBulletTest.setOutlineColor(Color::White);
	enemyBulletTest.setOutlineThickness(1);
	enemyBullet.shape = enemyBulletTest;
	enemyBullet.direction = direction;
	enemyBullet.speed = 600.0f;
	enemyBullet.position = position;
	enemyBullet.shape.setPosition(enemyBullet.position);
	enemyBullet.direction.y = 1.0f;
	//push enemyBullet
	game.EnemyBullets.push_back(enemyBullet);
}

//destroy Enemy when out of screen
void destroyEnemy(Game& game) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		if ((*it).position.y > 1000 ||  (*it).position.x > 1500 || (*it).position.x < 420) {
			game.Enemies.erase(it);
			break;
		}
	}
}

//destroy EnemyBullet when out of screen
void destroyEnemyBullet(Game& game) {
	for (std::list<EnemyBullet>::iterator it = game.EnemyBullets.begin(); it != game.EnemyBullets.end(); it++) {
		if ((*it).position.y > 1000) {
			game.EnemyBullets.erase(it);
			break;
		}
	}
}












