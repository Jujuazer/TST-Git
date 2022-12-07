#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
using namespace sf;

void AddParticleToSystem (ParticleSystem& particleSys, float lifeTime) {
	Particle part;

	const float PI = 3.14159265;
	float angle = PI * 2.0f * (float)rand() / RAND_MAX;
	float distance = particleSys.radius * sqrt((float)rand() / RAND_MAX);
	float x = particleSys.origin.x + cos(angle) * distance;
	float y = particleSys.origin.y + sin(angle) * distance;

	part.circleShape.setPosition({ x, y });
	part.circleShape.setRadius(particleSys.radius);

	part.lifeTime = lifeTime;
	particleSys.particles.push_back(part);
}

void UpdateParticleSystem(ParticleSystem& particleSys, float deltaTime) {
	for (std::list<Particle>::iterator it = particleSys.particles.begin(); it != particleSys.particles.end(); it++) {
		(*it).timeCounter += deltaTime;
		//std::cout << (*it).timeCounter << std::endl;
		if ((*it).timeCounter > (*it).lifeTime) {
			it = particleSys.particles.erase(it);
			it--;
		}
	}

	particleSys.timerCreateParticle += deltaTime;

	std::cout << particleSys.timerCreateParticle << std::endl;

	if (particleSys.timerCreateParticle > particleSys.CreateParticleDelay) {
		particleSys.timerCreateParticle = 0.0f;
		float lifeTime = rand() % (int)particleSys.maxLifeTimeParticle + particleSys.minLifeTimeParticle;
		AddParticleToSystem(particleSys, lifeTime);
	}
}

void  ClearParticleSystem(ParticleSystem& particleSys) {
	particleSys.particles.clear();
	particleSys.timerCreateParticle = 0;
}

ParticleSystem CreateParticleSystem(float CreateParticleDelay, float minLifeTimeParticle, float maxLifeTimeParticle, float radius, float sizeParticle) {
	ParticleSystem partSys;
	partSys.CreateParticleDelay = CreateParticleDelay;
	partSys.maxLifeTimeParticle = maxLifeTimeParticle;
	partSys.minLifeTimeParticle = minLifeTimeParticle;
	partSys.radius = radius;
	partSys.sizeParticle = sizeParticle;

	return partSys;
}

void DrawParticleSystem(ParticleSystem& particleSys, RenderWindow& window) {

	for (std::list<Particle>::iterator it = particleSys.particles.begin(); it != particleSys.particles.end(); it++) {
		window.draw((*it).circleShape);
	}
}