#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

struct Game;

struct Enemy {
	ConvexShape shape;
	ConvexShape shape2;
	Vector2f position;
	Vector2f direction;
	float speed = 50.0f;
};

void setupEnemy(Enemy& enemy, RenderWindow& window, Vector2f direction, Game& game);

void updateEnemy(Game& game, float deltaTime);





