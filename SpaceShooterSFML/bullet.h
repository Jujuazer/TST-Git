#pragma once
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;

struct Bullet {
    ConvexShape bulletForm;

    Vector2f position;
    Vector2f size;
    float speed = 400;
    float rotationAngle = 0;

    Vector2f direction;
};
