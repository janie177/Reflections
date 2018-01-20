#include "CloudEffect.h"
#include "Random.h"

reflections::CloudEffect::CloudEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) : ParticleEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset) {
}

void reflections::CloudEffect::updateParticle(Particle * particle, double dt) {
}

void reflections::CloudEffect::onParticleSpawn(Particle * particle) {
	double x = Random::getInstance().randomDouble(0, 2) - 1;
	double y = Random::getInstance().randomDouble(0, 2) - 1;
	particle->setDirection(x, y);
}

void reflections::CloudEffect::onParticleDeath(Particle * particle) {
}

void reflections::CloudEffect::onUpdate(double dt) {
}
