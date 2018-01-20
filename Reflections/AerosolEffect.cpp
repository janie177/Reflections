#include "AerosolEffect.h"
#include "Random.h"
#include <iostream>
#include <cmath>

reflections::AerosolEffect::AerosolEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) : ParticleEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset) {
	origin.set(0, 0);
	lastCamX = 0;
	lastCamY = 0;
}

void reflections::AerosolEffect::updateParticle(Particle * particle, double dt) {
	particle->setDirection(particle->getDirection().getX() + (Random::getInstance().randomDouble(0, 0.2) - 0.1), particle->getDirection().getY() + (Random::getInstance().randomDouble(0, 0.2) - 0.1));
}

void reflections::AerosolEffect::onParticleSpawn(Particle * particle) {
	double x, y;
	translateLocation(0, 0, x, y);
	x = -x + Random::getInstance().randomInt(0, screenW);
	y -= Random::getInstance().randomInt(0, screenH);

	particle->setX(x);
	particle->setY(y);

	double xDir, yDir;
	xDir = Random::getInstance().randomDouble(0, 2) - 1;
	yDir = Random::getInstance().randomDouble(0, 2) - 1;
	particle->setDirection(xDir, yDir);
}

//Not used because aerosol particles never die.
void reflections::AerosolEffect::onParticleDeath(Particle * particle) {
}

//Aerosols are not location bound. Override the default distance check.
bool reflections::AerosolEffect::isActive() {
	return true;
}

//When a particle is no longer visible, move it so it appears on the opposite side of the screen.
void reflections::AerosolEffect::onUpdate(double dt) {
	//This is to make sure the particles don't all heap up when a lot of particles suddenly resposition at the same time.
	if (abs(camX - lastCamX) > screenW / 10 || abs(camY - lastCamY) > screenH / 10) {
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
		}
	}
}

//Never kill aerosol particles. just detect when they stray too far and respawn them.
bool reflections::AerosolEffect::killCheck(Particle * particle) {
	return false;
}

void reflections::AerosolEffect::reset() {
	for (Particle & const particle : particles) {
		onParticleSpawn(&particle);
	}
}
