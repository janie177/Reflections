#include "RisingEffect.h"

reflections::RisingEffect::RisingEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) : ParticleEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset) {
}

void reflections::RisingEffect::updateParticle(Particle * particle, double dt) {
}

void reflections::RisingEffect::onParticleSpawn(Particle * particle) {
	double x, y;
	x = Random::getInstance().randomDouble(0, 0.7) - 0.35;
	y = 1;

	particle->setDirection(x, y);
}

void reflections::RisingEffect::onParticleDeath(Particle * particle) {
}

void reflections::RisingEffect::onUpdate(double dt) {
}
