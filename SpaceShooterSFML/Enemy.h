#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "bullet.h"
using namespace sf;

struct Game;

struct Enemy {
	ConvexShape shape;
	ConvexShape shape2;
	Vector2f position;
	Vector2f direction;
	float speed = 50.0f;
	float speedCounter = 0.0f;
	float speedDelay = 0.0f;
	bool hasSpeed = false;
	float shootCounter = 0.0f;
	float shootDelay = 0.0f;
};

void setupEnemy(Enemy& enemy, RenderWindow& window, Vector2f direction, Game& game);

void updateEnemy(Game& game, float deltaTime);

void setupEnemyBullet(EnemyBullet& enemyBullet, RenderWindow& window, Vector2f direction, Game& game, Vector2f position);

//Destroy enemy when out of screen
void destroyEnemy(Game& game);

void destroyEnemyBullet(Game& game);



