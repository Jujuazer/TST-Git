#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
#include "game.h"
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

    bool isMoving;
};

void setupSpaceShip(SpaceShip& spaceShip, Vector2f spaceShipPosition, Vector2f spaceShipSize);

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window);

void move(SpaceShip& spaceShip, Vector2f direction, float deltaTime);

void rotateShip(SpaceShip& spaceShip, Vector2f direction);

void SetSpaceShipPosition(SpaceShip& spaceShip, Vector2f position);

void PlayStageCollision(SpaceShip& spaceShip, RenderWindow& window, Vector2f& direction);

void Shoot(SpaceShip& spaceShip, Game& game, Vector2f direction);

