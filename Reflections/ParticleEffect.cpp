#include "ParticleEffect.h"
#include "GameManager.h"
#include "Random.h"
#include "Background.h"
#include <iostream>
#include <cmath>

using namespace reflections;

reflections::ParticleEffect::ParticleEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) {
	this->activationRange = activationRange;
	this->particleRange = particleRange;
	Renderer & renderer = GameManager::getInstance().getRenderer();
	this->layerMultiplier = Background::getLayerMultiplier(layer);
	origin.set(x, y);
	this->totalParticles = totalParticles;
	this->totalChance = 0;
	this->particleCount = 0;
	this->totalCounter = 0;
	this->age = 0;
	this->spawnThreshold = 0;
	this->lastTick = 0;
	this->camX = 0;
	this->camY = 0;
	this->spawnXOffset = spawnXOffset;
	this->spawnYOffset = spawnYOffset;
	
	this->layer = layer;
	this->screenW = renderer.getScreenWidth();
	this->screenH = renderer.getScreenHeight();
	this->lifeSpan = lifeSpan;
	this->particlesPerSecond = pps;
	this->maxParticles = pCount;

	particleAge.setMin(pAgeMin);
	particleAge.setMax(pAgeMax);

	particleSpeed.setMin(pSpeedMin);
	particleSpeed.setMax(pSpeedMax);

	Particle particle;
	for (int i = 0; i < maxParticles; i++) {
		particles.push_back(particle);
	}
}

ParticleEffect * reflections::ParticleEffect::addParticleType(int id, double pct) {
	particleIDs[id] = pct;
	this->totalChance += pct;
	return this;
}

bool reflections::ParticleEffect::isActive() {
	double dx, dy, distance;
	translateLocation(origin.getX(), origin.getY(), dx, dy);
	distance = sqrt(pow((screenW / 2) - dx, 2) + pow((screenH / 2) - dy, 2));
	return distance <= activationRange;
}

int reflections::ParticleEffect::getLayer() {
	return layer;
}

bool reflections::ParticleEffect::update() {
	int amountToSpawn, spawned = 0;
	double max, originX, originY, x, y;
	//If effect is too old, return false.
	if (lifeSpan > 0 && age > lifeSpan) {
		return false;
	}

	//If the effect is currently not active, don't do anything and return true.
	if (!isActive()) {
		return true;
	}

	spawnThreshold += GameManager::getInstance().getGameTimer().secondsSinceTick();
	amountToSpawn = particlesPerSecond * spawnThreshold;

	if (amountToSpawn > 0) {
		spawnThreshold = 0;
		max = maxParticles - particleCount;
		if (max < amountToSpawn) {
			amountToSpawn = max;
		}
	}

	//Calculate where on the screen the origin is.
	//originX = (origin.getX() - (camX - (screenW / 2))) * layerMultiplier;
	//originY = (screenH - (origin.getY() - (camY - (screenH / 2)))) * layerMultiplier;
	translateLocation(origin.getX(), origin.getY(), originX, originY);

	for (Particle & const particle : particles) {
		if (particle.isAlive()) {

			particle.getTextureData().update();
			x = originX + particle.getX();
			y = originY - particle.getY();

			if (killCheck(&particle)) {
				particle.kill();
				particleCount--;
				onParticleDeath(&particle);
			}
		}

		//If the particle is dead and there's still a need for new particles to be spawned, spawn it again.
		if (spawned < amountToSpawn && !particle.isAlive() && (totalParticles == 0 || totalCounter <= totalParticles)) {
			spawnParticle(&particle);
			spawned++;
			totalCounter++;
		}
	}
	return true;
}

void reflections::ParticleEffect::render(SDL_Renderer * renderer, double deltaSeconds, double cameraX, double cameraY) {
	//Update local camera positions
	this->camX = cameraX;
	this->camY = cameraY;

	//If the effect is currently not active, return.
	if (!isActive()) {
		return;
	}

	//Reused data.
	double x, y, originX, originY;
	SDL_Rect dest;

	age += deltaSeconds;

	//Call onUpdate for general updating for each frame.
	onUpdate(deltaSeconds);

	//Calculate where on the screen the origin is.
	//originX = (origin.getX() - (cameraX - (screenW / 2))) * layerMultiplier;
	//originY = (screenH - (origin.getY() - (cameraY - (screenH / 2)))) * layerMultiplier;
	translateLocation(origin.getX(), origin.getY(), originX, originY);

	int pID;
	for (auto itr = particleIDs.begin(); itr != particleIDs.end(); itr++) {
		pID = itr->first;
		for (Particle & const particle : particles) {
			if (particle.isAlive() && particle.getTextureID() == pID) {
				//Let each effect alter particles before they are updated.
				updateParticle(&particle, deltaSeconds);

				//Update the particle
				particle.update(deltaSeconds);

				//Calculate the X and Y coordinate of the particle on the screen (So on the layer that it is drawn on).
				x = originX + particle.getX();
				y = originY - particle.getY();

				//Finally, update the particles texture if a tick has passed and draw it on the screen.

				dest.w = particle.getTextureData().getTexture()->getFrameWidth();
				dest.h = particle.getTextureData().getTexture()->getHeight();
				dest.x = x;
				dest.y = y;

				//Copy texture onto screen.
				SDL_RenderCopy(renderer, particle.getTextureData().getTexture()->getTexture(), particle.getTextureData().getFramePosition(), &dest);
			}
		}
	}
}

//Check if a particle should die. This occurs when they travelled too far from their origin or when they outlived their lifepsan.
bool reflections::ParticleEffect::killCheck(Particle * particle) {
	return ((particle->getMaxAge() > 0 && particle->getAge() > particle->getMaxAge()) || (particleRange > 0 && particle->getDistance() > particleRange));
}

void reflections::ParticleEffect::spawnParticle(Particle * particle) {
	particleCount++;

	int textureID;
	double chance = 0, roll = Random::getInstance().randomDouble(0, totalChance);
	for (auto & const idEntry : particleIDs) {
		chance += idEntry.second;
		if (roll <= chance) {
			textureID = idEntry.first;
			break;
		}
	}

	double age = Random::getInstance().randomDouble(particleAge.getMin(), particleAge.getMax());
	double speed = Random::getInstance().randomDouble(particleSpeed.getMin(), particleSpeed.getMax());

	double x = Random::getInstance().randomDouble(0, 2 * spawnXOffset) - spawnXOffset;
	double y = Random::getInstance().randomDouble(0, 2 * spawnYOffset) - spawnYOffset;

	particle->spawn(age, speed, textureID);
	particle->setX(x);
	particle->setY(y);
	onParticleSpawn(particle);
}

//Use camera location to find where on the screen this particle effect should render.
void reflections::ParticleEffect::translateLocation(double worldX, double worldY, double & x, double & y) {
	x = worldX - (camX - (screenW / 2));
	y = screenH - (worldY - (camY - (screenH / 2)));
	x *= layerMultiplier;
	y *= layerMultiplier;
}
