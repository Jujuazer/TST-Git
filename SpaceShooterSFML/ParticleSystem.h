#pragma once
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;

struct Particle
{
	float lifeTime;
	float timeCounter;
	CircleShape circleShape;
};

struct ParticleSystem {
	std::list<Particle> particles;
	float CreateParticleDelay = 1;
	float timerCreateParticle = 0;

	float minLifeTimeParticle = 1;
	float maxLifeTimeParticle = 2;

	Vector2f origin;
	float radius = 1;
	float sizeParticle = 1;
};

void AddParticleToSystem(ParticleSystem& particleSys, float lifeTime);
void  ClearParticleSystem(ParticleSystem& particleSys);
ParticleSystem CreateParticleSystem(float CreateParticleDelay, float minLifeTimeParticle, float maxLifeTimeParticle, float radius, float sizeParticle);
void UpdateParticleSystem(ParticleSystem& particleSys, float deltaTime);
void DrawParticleSystem(ParticleSystem& particleSys, RenderWindow& window);


