#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
using namespace sf;

struct SpaceShip;

struct Game
{
	std::list<Bullet> Bullets;
	float originalDeltaTime;
};

void MoveBullets(Game& game, float deltaTime);

void DrawBullets(Game& game, RenderWindow& window);

void SlowDown(Game& game, float& deltaTime, float divideValue = 2);

void ResetDeltaTime(Game& game, float& deltaTime);

void HandleKeyInput(Vector2f& direction);