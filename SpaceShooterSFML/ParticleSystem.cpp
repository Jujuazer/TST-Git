#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
using namespace sf;

const float PI = 3.14159265;

void AddParticleToSystem (ParticleSystem& particleSys, float lifeTime) {
	Particle part;

	part.angle = PI * 2.0f * (float)rand() / RAND_MAX;
	part.distance = particleSys.radius * sqrt((float)rand() / RAND_MAX);

	float x = particleSys.origin.x + cos(part.angle) * part.distance;
	float y = particleSys.origin.y + sin(part.angle) * part.distance;

	part.circleShape.setPosition({ x, y });
	part.position = { x, y };

	//random avec premier nombre qui est l'amplitude (ex : 100 a 300, amplitude = 200) deuxieme est le mini alors : min = 100 donc generation rand() % 200 + 100;

	float randomRadiusParticle = (particleSys.radius * 0.7f) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((particleSys.radius * 1.3f) - (particleSys.radius * 0.7f))));

	part.circleShape.setRadius(randomRadiusParticle);
	part.circleShape.setOrigin({ 0, 0 });

	if (particleSys.direction == Vector2f{0, 0}) {
		Vector2f dir = Vector2f(cos(part.angle), sin(part.angle));
		part.direction = dir;
	}
	else {
		part.direction = particleSys.direction;
	}

	part.lifeTime = lifeTime;
	particleSys.particles.push_back(part);
}


void UpdateParticleSystem(ParticleSystem& particleSys, float deltaTime) {

	for (std::list<Particle>::iterator it = particleSys.particles.begin(); it != particleSys.particles.end(); it++) {
		(*it).timeCounter += deltaTime;

		if ((*it).timeCounter > (*it).lifeTime) {
			it = particleSys.particles.erase(it);
			if (it == particleSys.particles.end()) { break; }
		}

		float scale = sin(PI * (*it).timeCounter / (*it).lifeTime );
		(*it).circleShape.setScale({scale, scale});

		float x = particleSys.origin.x + cos((*it).angle) * (*it).distance;
		float y = particleSys.origin.y + sin((*it).angle) * (*it).distance;

		(*it).circleShape.setPosition({ x, y });
		(*it).position = { x, y };

		(*it).position += (*it).direction * (*it).speed * deltaTime;
		(*it).circleShape.setPosition((*it).position);


		//std::cout << (*it).timeCounter << std::endl;
	}

	particleSys.timerCreateParticle += deltaTime;

	if (particleSys.timerCreateParticle > particleSys.CreateParticleDelay) {

		particleSys.timerCreateParticle = 0.0f;
		float lifeTime = rand() % (int)particleSys.maxLifeTimeParticle + particleSys.minLifeTimeParticle;

		std::cout << "new particle created and life time : " << lifeTime << std::endl;
		AddParticleToSystem(particleSys, lifeTime);
	}
}

void ClearParticleSystem(ParticleSystem& particleSys) {
	particleSys.particles.clear();
	particleSys.timerCreateParticle = 0;
}

ParticleSystem CreateParticleSystem(float CreateParticleDelay, float minLifeTimeParticle, float maxLifeTimeParticle, float radius, float sizeParticle, Vector2f direction, Vector2f origin) {
	ParticleSystem partSys;
	partSys.CreateParticleDelay = CreateParticleDelay;
	partSys.maxLifeTimeParticle = maxLifeTimeParticle;
	partSys.minLifeTimeParticle = minLifeTimeParticle;
	partSys.radius = radius;
	partSys.sizeParticle = sizeParticle;
	partSys.direction = direction;
	partSys.origin = origin;

	return partSys;
}

void DrawParticleSystem(ParticleSystem& particleSys, RenderWindow& window) {

	for (std::list<Particle>::iterator it = particleSys.particles.begin(); it != particleSys.particles.end(); it++) {
		window.draw((*it).circleShape);
	}
}