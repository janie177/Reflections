#include "DripEffect.h"

reflections::DripEffect::DripEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) : ParticleEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset) {
}

void reflections::DripEffect::updateParticle(Particle * particle, double dt) {

}

void reflections::DripEffect::onParticleSpawn(Particle * particle) {
	double x = 0;
	double y = -1;
	particle->setDirection(x, y);
}

void reflections::DripEffect::onParticleDeath(Particle * particle) {
}

void reflections::DripEffect::onUpdate(double dt) {
}
