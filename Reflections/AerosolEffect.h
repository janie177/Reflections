#pragma once
#include "ParticleEffect.h"

namespace reflections {
	class AerosolEffect : public ParticleEffect {
	private:
		double lastCamX, lastCamY;
	public:
		AerosolEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset);
		void updateParticle(Particle * particle, double dt);
		void onParticleSpawn(Particle * particle);
		void onParticleDeath(Particle * particle);
		void onUpdate(double dt);

		bool isActive();
		bool killCheck(Particle * particle);
		void reset();
	};
}