#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
using namespace sf;

struct Game
{
	std::list<Bullet> Bullets;
};

void MoveBullets(Game& game, float deltaTime);

void DrawBullets(Game& game, RenderWindow& window);



