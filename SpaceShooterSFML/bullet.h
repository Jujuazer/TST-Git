#pragma once
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;

struct Bullet {
    ConvexShape bulletForm;
	RectangleShape boxCollider;

    Vector2f position;
    Vector2f size;
    float speed = 400;
    float rotationAngle = 0;

    Vector2f direction;
};

struct EnemyBullet {
	ConvexShape shape;
	RectangleShape boxCollider;

	Vector2f position;
	Vector2f size;
	float speed = 300;
	float rotationAngle = 0;

	Vector2f direction;
};
