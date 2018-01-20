#include "FountainEffect.h"
#include "Random.h"

reflections::FountainEffect::FountainEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) : ParticleEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset) {
}

void reflections::FountainEffect::updateParticle(Particle * particle, double dt) {
	particle->getDirection().add(0, -((particle->getSpeed() / 100) * particle->getAge() * dt));
}

void reflections::FountainEffect::onParticleSpawn(Particle * particle) {
	double x, y;
	x = Random::getInstance().randomDouble(0.35, 1.35) - 0.7;
	y = 1;

	particle->setDirection(x, y);
}

void reflections::FountainEffect::onParticleDeath(Particle * particle) {
}

void reflections::FountainEffect::onUpdate(double dt) {
}
