#include "ParticleManager.h"
#include "AerosolEffect.h"
#include "FountainEffect.h"
#include "RainEffect.h"
#include "CloudEffect.h"
#include "DripEffect.h"
#include "RisingEffect.h"

using namespace reflections;

ParticleEffect * reflections::ParticleManager::create(EffectType type, double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) {
	ParticleEffect * effect = nullptr;
	switch (type) {
	case AEROSOLS:
		effect = new AerosolEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
		break;
	case FOUNTAIN:
		effect = new FountainEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
		break;
	case RAIN:
		effect = new RainEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
		break;
	case CLOUD:
		effect = new CloudEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
		break;
	case DRIP:
		effect = new DripEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
		break;
	case RISING:
		effect = new RisingEffect(x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
		break;
	}
	return effect;
}
