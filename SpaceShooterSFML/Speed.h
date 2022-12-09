#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
#include "game.h"
#include "ParticleSystem.h"
#include "UI.h"
using namespace sf;

enum shootMode {
    SINGLE,
    BISHOT,
    LASER,
    TARGETMISSILE
};

struct SpaceShip
{
    // put everything about the space ship specs

    ConvexShape spaceship1;
    ConvexShape spaceship2;
    ConvexShape spaceship3;

    RectangleShape boxCollider;

    Vector2f position;
    float size;
    float speed = 400;

    float rotationAngle = 0;
    float shootDelay;
    float shootCounter;

    bool shootOpen = true;
    bool isMoving = false;

    shootMode shootmode = SINGLE;

    ParticleSystem backAnim;
    ParticleSystem backAnim2;
};

void CheckEnemyBulletCollision(Game& game, SpaceShip& spaceShip, GameOver& gameOver, GAMESTATE& gameState);

void setupSpaceShip(SpaceShip& spaceShip, Vector2f spaceShipPosition, float spaceShipSize, float shootDelay);

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window);

void move(SpaceShip& spaceShip, Vector2f direction, float deltaTime);

void rotateShip(SpaceShip& spaceShip, Vector2f direction);

void SetSpaceShipPosition(SpaceShip& spaceShip, Vector2f position);

void PlayStageCollision(SpaceShip& spaceShip, RenderWindow& window, Vector2f& direction);

void Shoot(SpaceShip& spaceShip, Game& game, Vector2f direction);

void CheckEnemyCollision(Game& game, SpaceShip& spaceShip, GameOver& gameOver, GAMESTATE& gameState);