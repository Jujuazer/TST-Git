#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <random>
#include "game.h"
using namespace sf;

float randomXposition() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(460, 1460);
	return dis(gen);
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
	enemyTest.setPosition(Vector2f{ a ,0.f});
	enemyTest.setFillColor(Color::Red);
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
	enemyTest2.setPosition(Vector2f{ a, 0.0f });
	
	


	enemy.shape = enemyTest;
	enemy.shape2 = enemyTest2;
	enemy.direction = direction;
	enemy.speed = 100.0f;
	enemy.position = Vector2f{ a , 0.f };
	enemy.shape.setPosition(enemy.position);
	enemy.direction.y = 1.0f;
	
	//push enemy
	game.Enemies.push_back(enemy);
}




void updateEnemy(Game& game, float deltaTime) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		float deltaX = (*it).speed * (*it).direction.x * deltaTime;
		float deltaY = (*it).speed * (*it).direction.y * deltaTime;
		(*it).position.y += deltaY;

		(*it).shape.setPosition((*it).position);
		(*it).shape2.setPosition((*it).position);
		

	} 
}
	






