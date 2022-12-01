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

};

void setupSpaceShip(SpaceShip& spaceShip, Vector2f spaceShipPosition, Vector2f spaceShipSize);

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window);
