#define _USE_MATH_DEFINES
#include <iostream>
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

void move(SpaceShip& spaceShip, Vector2f direction, float deltaTime) {

	float deltaX = spaceShip.speed * direction.x * deltaTime;
	float deltaY = spaceShip.speed * direction.y * deltaTime;
	spaceShip.position.x += deltaX;
	spaceShip.position.y += deltaY;

	spaceShip.spaceship1.setPosition(spaceShip.position);
	spaceShip.spaceship2.setPosition(spaceShip.position);
	spaceShip.spaceship3.setPosition(spaceShip.position);
}

// put vector2 on lenght = 1
void normalizeVector(Vector2f& vector) {

	float xy = (vector.x * vector.x) + (vector.y * vector.y);
	float lenght = 0;

	if (xy > 0) {
		lenght = sqrt(xy);
		vector.x = round(vector.x / lenght);
		vector.y = round(vector.y / lenght);
	}

	else {
		vector.x = 0;
		vector.y = 0;
	}
}

void rotateShip(SpaceShip& spaceShip, Vector2f direction) {
	float angleDegs;
	float angleRads;

	angleRads = std::atan2(-direction.y, direction.x);
	angleDegs = 90 - angleRads * 180.0 / M_PI;
	std::cout << angleDegs << std::endl;

	if (angleDegs > 45 && angleDegs < 315) {
		angleDegs = 0;
	}
	
	if (direction.x == 0 && direction.y == 0) {
		angleDegs = spaceShip.rotationAngle;
	}

	spaceShip.rotationAngle = angleDegs;

	spaceShip.spaceship1.setRotation(angleDegs);
	spaceShip.spaceship2.setRotation(angleDegs);
	spaceShip.spaceship3.setRotation(angleDegs);
}
