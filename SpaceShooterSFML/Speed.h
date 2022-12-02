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
    
    std::list<Bullet> Bullets;
};

void setupSpaceShip(SpaceShip& spaceShip, Vector2f spaceShipPosition, Vector2f spaceShipSize);

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window);

void move(SpaceShip& spaceShip, Vector2f direction, float deltaTime);

void rotateShip(SpaceShip& spaceShip, Vector2f direction);

void SetSpaceShipPosition(SpaceShip& spaceShip, Vector2f position);

void PlayStageCollision(SpaceShip& spaceShip, RenderWindow& window, Vector2f& direction);

void MoveBullets(SpaceShip& spaceShip, float deltaTime);

void DrawBullets(SpaceShip& spaceShip, RenderWindow& window);

void Shoot(SpaceShip& spaceShip, Vector2f direction);

