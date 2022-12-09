#define _USE_MATH_DEFINES
#include <iostream>
#include "speed.h"
#include "math.h"
#include "Enemy.h"
#include "UI.h"
#include <SFML/Graphics.hpp>

struct Game;

const int leftBound = 460;
const int rightBound = 1460;
const float biShotAngle = 10;
const int xOffsetBox = 18;
const int yOffsetBox = 40;

void setupSpaceShip(SpaceShip& spaceShip , Vector2f spaceShipPosition, float spaceShipSize, float shootDelay) {

	spaceShip.position = spaceShipPosition;
	spaceShip.size = spaceShipSize;
	spaceShip.spaceship1.setPointCount(4);
	spaceShip.spaceship1.setPoint(0, Vector2f(0 * spaceShipSize, -75 * spaceShipSize));
	spaceShip.spaceship1.setPoint(1, Vector2f(-25 * spaceShipSize, 20 * spaceShipSize));
	spaceShip.spaceship1.setPoint(2, Vector2f(0 * spaceShipSize, 30 * spaceShipSize));
	spaceShip.spaceship1.setPoint(3, Vector2f(25 * spaceShipSize, 20 * spaceShipSize));
	spaceShip.spaceship1.setPosition(spaceShipPosition);

	spaceShip.spaceship2.setPointCount(4);
	spaceShip.spaceship2.setPoint(0, Vector2f(0 * spaceShipSize, -15 * spaceShipSize));
	spaceShip.spaceship2.setPoint(1, Vector2f(-60 * spaceShipSize, 15 * spaceShipSize));
	spaceShip.spaceship2.setPoint(2, Vector2f(0 * spaceShipSize, 20 * spaceShipSize));
	spaceShip.spaceship2.setPoint(3, Vector2f(60 * spaceShipSize, 15 * spaceShipSize));
	spaceShip.spaceship2.setFillColor(Color(200, 200, 200));
	spaceShip.spaceship2.setPosition(spaceShipPosition);

	spaceShip.spaceship3.setPointCount(3);
	spaceShip.spaceship3.setPoint(0, Vector2f(0 * spaceShipSize, 20 * spaceShipSize));
	spaceShip.spaceship3.setPoint(1, Vector2f(-50 * spaceShipSize, -5 * spaceShipSize));
	spaceShip.spaceship3.setPoint(2, Vector2f(50 * spaceShipSize, -5 * spaceShipSize));
	spaceShip.spaceship3.setFillColor(Color(150, 150, 150));
	spaceShip.spaceship3.setPosition(spaceShipPosition);


	float width = spaceShip.spaceship1.getGlobalBounds().width;
	float height = spaceShip.spaceship1.getGlobalBounds().height;
	

	spaceShip.boxCollider.setSize({width, height});
	spaceShip.boxCollider.setPosition(spaceShip.position);
	spaceShip.boxCollider.setOutlineColor(Color{ 255, 0, 0 });
	spaceShip.boxCollider.setOutlineThickness(2);

	spaceShip.shootDelay = shootDelay;

	spaceShip.backAnim = CreateParticleSystem(0.05f, 0.2f, 1, 5, 1, { 0, 1 }, {spaceShip.position.x + 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height});
	spaceShip.backAnim2 = CreateParticleSystem(0.05f, 0.2f, 1, 5, 1, { 0, 1 }, { spaceShip.position.x - 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height });
}

void updateDrawSpaceShip(SpaceShip& spaceShip, RenderWindow& window)
{
	window.draw(spaceShip.spaceship3);
	window.draw(spaceShip.spaceship2);
	window.draw(spaceShip.spaceship1);

	DrawParticleSystem(spaceShip.backAnim, window);
	DrawParticleSystem(spaceShip.backAnim2, window);

	//window.draw(spaceShip.boxCollider);
}

void CheckEnemyCollision(Game& game, SpaceShip& spaceShip, GameOver& gameOver, GAMESTATE& gameState) {
	for (std::list<Enemy>::iterator it = game.Enemies.begin(); it != game.Enemies.end(); it++) {
		if (IsOverlappingBoxOnBox(spaceShip.boxCollider.getPosition(), spaceShip.boxCollider.getSize(), (*it).boxCollider.getPosition(), (*it).boxCollider.getSize())) {
			DisplayGameOver(gameOver, gameState);
		}
	}
}

void SetSpaceShipPosition(SpaceShip& spaceShip, Vector2f position) {
	spaceShip.position = position;

	spaceShip.spaceship1.setPosition(spaceShip.position);
	spaceShip.spaceship2.setPosition(spaceShip.position);
	spaceShip.spaceship3.setPosition(spaceShip.position);

	spaceShip.boxCollider.setPosition({spaceShip.position.x - xOffsetBox, spaceShip.position.y - yOffsetBox});
}

void move(SpaceShip& spaceShip, Vector2f direction, float deltaTime) {

	float deltaX = spaceShip.speed * direction.x * deltaTime;
	float deltaY = spaceShip.speed * direction.y * deltaTime;
	spaceShip.position.x += deltaX;
	spaceShip.position.y += deltaY;

	spaceShip.backAnim.origin.x += deltaX;
	spaceShip.backAnim.origin.y += deltaY;

	spaceShip.backAnim2.origin.x += deltaX;
	spaceShip.backAnim2.origin.y += deltaY;

	SetSpaceShipPosition(spaceShip, spaceShip.position);
	UpdateParticleSystem(spaceShip.backAnim, deltaTime);
	UpdateParticleSystem(spaceShip.backAnim2, deltaTime);
}

void rotateShip(SpaceShip& spaceShip, Vector2f direction) {
	float angleDegs;
	float angleRads;

	angleRads = std::atan2(-direction.y, direction.x);
	angleDegs = 90 - angleRads * 180.0 / M_PI;
	//std::cout << angleDegs << std::endl;

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

void CheckEnemyBulletCollision(Game& game, SpaceShip& spaceShip, GameOver& gameOver, GAMESTATE& gameState) {
	for (std::list<EnemyBullet>::iterator it = game.EnemyBullets.begin(); it != game.EnemyBullets.end(); it++) {

		if (IsOverlappingBoxOnBox((*it).boxCollider.getPosition(), (*it).boxCollider.getSize(), spaceShip.boxCollider.getPosition(), spaceShip.boxCollider.getSize())) {
			it = game.EnemyBullets.erase(it);
			DisplayGameOver(gameOver, gameState);
			break;
		}
	}
}

void Shoot(SpaceShip& spaceShip, Game& game, Vector2f direction) {

	//spaceShip.Bullets.push_back(Bullet{ spaceShip.position, spaceShip.size, 400, direction });
	if (direction.x == 0 && direction.y == 0) {
		direction.y = -1;
	}

	Bullet x;

	if ((direction.x == 1 || direction.x == -1) && direction.y == 0) { direction.x = 0; direction.y = -1; }
	if (direction.y > 0) { direction.y = -1; direction.x = 0; }

	if (spaceShip.shootmode == 0) {

		x.direction = direction;
		x.rotationAngle = spaceShip.rotationAngle;
	}

	x.position = spaceShip.position;
	x.speed = 800;

	if (spaceShip.shootmode == 1) {
		Bullet y;

		x.direction = ConvertAngleToDirection(ConvertVectorToDegree(direction) + biShotAngle);
		y.direction = ConvertAngleToDirection(ConvertVectorToDegree(direction) - biShotAngle);

		x.rotationAngle = ConvertVectorToDegree(x.direction);
		y.rotationAngle = ConvertVectorToDegree(y.direction, true, false);

		y.position = spaceShip.position;
		y.speed = 800;

		y.bulletForm.setPointCount(3);
		y.bulletForm.setPoint(0, Vector2f(0, -20));
		y.bulletForm.setPoint(1, Vector2f(-20, 10));
		y.bulletForm.setPoint(2, Vector2f(20, 10));
		y.bulletForm.setFillColor(Color(200, 200, 200));
		y.bulletForm.setPosition(y.position);
		y.bulletForm.setRotation(y.rotationAngle);

		game.Bullets.push_back(y);
	}

	if (spaceShip.shootmode == 2) {

	}

	x.bulletForm.setPointCount(3);
	x.bulletForm.setPoint(0, Vector2f(0, -20));
	x.bulletForm.setPoint(1, Vector2f(-20, 10));
	x.bulletForm.setPoint(2, Vector2f(20, 10));
	x.bulletForm.setFillColor(Color(200, 200, 200));
	x.bulletForm.setPosition(x.position);
	x.bulletForm.setRotation(x.rotationAngle);

	float width = x.bulletForm.getGlobalBounds().width;
	float height = x.bulletForm.getGlobalBounds().height;

	x.boxCollider.setSize({ width, height });
	x.boxCollider.setPosition(x.position);
	x.boxCollider.setOutlineColor(Color{ 255, 0, 0 });
	x.boxCollider.setOutlineThickness(2);

	game.Bullets.push_back(x);
}

void PlayStageCollision(SpaceShip& spaceShip, RenderWindow& window, Vector2f& direction) {

	//left
	if (spaceShip.position.x < leftBound + spaceShip.spaceship1.getGlobalBounds().width) {
		SetSpaceShipPosition(spaceShip, Vector2f { leftBound + spaceShip.spaceship1.getGlobalBounds().width ,spaceShip.position.y });
		spaceShip.backAnim.origin = { spaceShip.position.x + 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.backAnim2.origin = { spaceShip.position.x - 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.boxCollider.setPosition({ spaceShip.position.x - xOffsetBox, spaceShip.position.y - yOffsetBox });
	}

	//right  
	else if (spaceShip.position.x + spaceShip.spaceship1.getGlobalBounds().width > rightBound) {
		SetSpaceShipPosition(spaceShip, { rightBound - spaceShip.spaceship1.getGlobalBounds().width,spaceShip.position.y });
		spaceShip.backAnim.origin = { spaceShip.position.x + 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.backAnim2.origin = { spaceShip.position.x - 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.boxCollider.setPosition({ spaceShip.position.x - xOffsetBox, spaceShip.position.y - yOffsetBox });
	}

	//top
	else if (spaceShip.position.y < 0) {
		SetSpaceShipPosition(spaceShip, { spaceShip.position.x, 0 });
		spaceShip.backAnim.origin = { spaceShip.position.x + 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.backAnim2.origin = { spaceShip.position.x - 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.boxCollider.setPosition({ spaceShip.position.x - xOffsetBox, spaceShip.position.y - yOffsetBox });
	}

	//bottom 
	else if (spaceShip.position.y + spaceShip.spaceship1.getGlobalBounds().height > window.getSize().y) {
		SetSpaceShipPosition(spaceShip, { spaceShip.position.x, window.getSize().y - spaceShip.spaceship1.getGlobalBounds().height });
		spaceShip.backAnim.origin = { spaceShip.position.x + 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.backAnim2.origin = { spaceShip.position.x - 10, spaceShip.position.y + spaceShip.spaceship2.getGlobalBounds().height };
		spaceShip.boxCollider.setPosition({ spaceShip.position.x - xOffsetBox, spaceShip.position.y - yOffsetBox });
	}
}

void destroyBullet(Game& game) {
	for (std::list<Bullet>::iterator it = game.Bullets.begin(); it != game.Bullets.end(); it++) {
		if ((*it).position.y > 1000) {
			game.Bullets.erase(it);
			break;
		}
	}
}
