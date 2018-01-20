#include "RainEffect.h"
#include <iostream>

reflections::RainEffect::RainEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) : ParticleEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset) {
	origin.set(0, 0);
	lastCamX = 0;
	lastCamY = 0;
}

void reflections::RainEffect::updateParticle(Particle * particle, double dt) {

}

void reflections::RainEffect::onParticleSpawn(Particle * particle) {
	double x, y;
	translateLocation(0, 0, x, y);
	x = -x + Random::getInstance().randomInt(0, screenW);
	y -= Random::getInstance().randomInt(0, screenH);

	particle->setX(x);
	particle->setY(y);

	double xDir, yDir;
	particle->setDirection(-0.02, -1);
}

void reflections::RainEffect::onParticleDeath(Particle * particle) {
}

void reflections::RainEffect::onUpdate(double dt) {
	//This is to make sure the particles don't all heap up when a lot of particles suddenly resposition at the same time.
	if (abs(camX - lastCamX) > screenW / 20 || abs(camY - lastCamY) > screenH / 20) {
		reset();
	}
	lastCamX = camX;
	lastCamY = camY;

	double baseX, baseY, px, py;
	translateLocation(0, 0, baseX, baseY);

	for (Particle & const particle : particles) {
		px = baseX + particle.getX();
		py = baseY - particle.getY();

		if (px < -10) {
			particle.setX(-baseX + screenW);
		}
		else if (px > screenW + 10) {
			particle.setX(-baseX);
		}

		if (py < -10) {
			particle.setY(baseY - screenH);
		}
		else if (py > screenH + 10) {
			particle.setY(baseY);
			particle.setX(((camX - (screenW / 2)) * layerMultiplier) + Random::getInstance().randomInt(0, screenW));
		}
	}
}

bool reflections::RainEffect::isActive() {
	return true;
}

bool reflections::RainEffect::killCheck(Particle * particle) {
	return false;
}

void reflections::RainEffect::reset() {
	for (Particle & const particle : particles) {
		onParticleSpawn(&particle);
	}
}
