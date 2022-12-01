#include "Speed.h"
#include <SFML/Graphics.hpp>

void setupSpaceShip(SpaceShip& spaceShip , Vector2f spaceShipPosition, Vector2f spaceShipSize) {

	spaceShip.position = spaceShipPosition;
	spaceShip.size = spaceShipSize;
	spaceShip.spaceship1.setPointCount(3);
	spaceShip.spaceship1.setPoint(0, Vector2f(0, -75));
	spaceShip.spaceship1.setPoint(1, Vector2f(-25, 25));
	spaceShip.spaceship1.setPoint(2, Vector2f(25, 25));
	spaceShip.spaceship1.setPosition(spaceShipPosition);

	spaceShip.spaceship2.setPointCount(3);
	spaceShip.spaceship2.setPoint(0, Vector2f(0, -20));
	spaceShip.spaceship2.setPoint(1, Vector2f(-60, 10));
	spaceShip.spaceship2.setPoint(2, Vector2f(60, 10));
	spaceShip.spaceship2.setFillColor(Color(200, 200, 200));
	spaceShip.spaceship2.setPosition(spaceShipPosition);

	spaceShip.spaceship3.setPointCount(3);
	spaceShip.spaceship3.setPoint(0, Vector2f(0, 20));
	spaceShip.spaceship3.setPoint(1, Vector2f(-50, -5));
	spaceShip.spaceship3.setPoint(2, Vector2f(50, -5));
	spaceShip.spaceship3.setFillColor(Color(150, 150, 150));
	spaceShip.spaceship3.setPosition(spaceShipPosition);
}

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window)
{
	window.draw(spaceShip.spaceship3);
	window.draw(spaceShip.spaceship2);
	window.draw(spaceShip.spaceship1);
}
