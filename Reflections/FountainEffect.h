#pragma once
#include "ParticleEffect.h"

namespace reflections {
	class FountainEffect : public ParticleEffect {
	private:
	public:
		FountainEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset);
		void updateParticle(Particle * particle, double dt);
		void onParticleSpawn(Particle * particle);
		void onParticleDeath(Particle * particle);
		void onUpdate(double dt);
	};
}