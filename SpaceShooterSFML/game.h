#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
#include "Score.h"
using namespace sf;

struct Enemy;

struct Game
{
	std::list<Bullet> Bullets;
	std::list<EnemyBullet> EnemyBullets;
	std::list<Enemy> Enemies;
};

void MoveBullets(Game& game, float deltaTime);

void DrawBullets(Game& game, RenderWindow& window);

void drawEnemy(Game& game, RenderWindow& window);

void generateEnemy(Score& Gscore, Game& game, RenderWindow& window, Vector2f direction);

void ChangeEnemySpeed(Game& game, float deltaTime);

void EnemyShoot(Game& game, float deltaTime, RenderWindow& window);

void updateEnemyBullets(Game& game, float deltaTime);

void DrawEnemyBullets(Game& game, RenderWindow& window);



