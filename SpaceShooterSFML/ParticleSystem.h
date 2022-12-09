#pragma once
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;

struct Particle
{
	float lifeTime;
	float timeCounter = 0;
	CircleShape circleShape;

	float angle = 0;
	float distance = 0;
	Vector2f direction = {0,0};
	float speed = 100;

	Vector2f position = { 0,0 };
};

struct ParticleSystem {
	std::list<Particle> particles;
	float CreateParticleDelay = 1;
	float timerCreateParticle = 0;

	float minLifeTimeParticle = 1;
	float maxLifeTimeParticle = 2;

	Vector2f origin = {0, 0};
	float radius = 1;
	float sizeParticle = 1;

	Vector2f direction = {0,0};
};

void AddParticleToSystem(ParticleSystem& particleSys, float lifeTime);
void  ClearParticleSystem(ParticleSystem& particleSys);
ParticleSystem CreateParticleSystem(float CreateParticleDelay, float minLifeTimeParticle, float maxLifeTimeParticle, float radius, float sizeParticle, Vector2f direction, Vector2f origin);
void UpdateParticleSystem(ParticleSystem& particleSys, float deltaTime);
void DrawParticleSystem(ParticleSystem& particleSys, RenderWindow& window);


