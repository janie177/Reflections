#pragma once
#include "ParticleEffect.h"

/*
	This class handles creation of Particle Effects.
	Each Particle Effect has its own layer to render the particles on.
	It renders and updates every frame (For smooth animation) and uses the time since last frame to calculate new locations of particles.

	Each Particle Effect has a type which is defined in the enum below.
	These are basically presets of parameters which I will use often.

	Each Particle Effect has its own class which inherits the abstract methods for manipulating spawned particles and altering them each frame.
*/

namespace reflections {

	enum EffectType {
		AEROSOLS,
		FOUNTAIN,
		RAIN,
		CLOUD,
		DRIP,
		RISING
	};

	class ParticleManager {
	private:
	public:
		static ParticleEffect * create(EffectType type, double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset);
	};

}