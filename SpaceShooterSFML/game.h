#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
using namespace sf;

enum GAMESTATE {
	PLAYING = 0,
	GAMEOVER = 1,
};

struct Game
{
	std::list<Bullet> Bullets;
};

void MoveBullets(Game& game, float deltaTime);

void DrawBullets(Game& game, RenderWindow& window);


