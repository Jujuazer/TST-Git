#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct SpaceShip
{
    // put everything about the space ship specs

    ConvexShape spaceship1;
    ConvexShape spaceship2;
    ConvexShape spaceship3;

    Vector2f position;
    Vector2f size;
    float speed = 400;

    float rotationAngle = 0;
};

void setupSpaceShip(SpaceShip& spaceShip, Vector2f spaceShipPosition, Vector2f spaceShipSize);

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window);

void move(SpaceShip& spaceShip, Vector2f direction, float deltaTime);

void normalizeVector(Vector2f& vector);

void rotateShip(SpaceShip& spaceShip, Vector2f direction);
