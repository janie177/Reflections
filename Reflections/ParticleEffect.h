#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <vector>
#include "Range.h"
#include "Particle.h"

namespace reflections {	
	class ParticleEffect {
	private:
		double age, lifeSpan;
		double activationRange;
		double particleRange;
		double particlesPerSecond;
		int particleCount, maxParticles, totalParticles;
		int totalCounter;
		int layer;
		long long int lastTick;
		double spawnThreshold;
		std::map<int, double> particleIDs;	//ID|%
		double totalChance;
		Range<double> particleAge;
		Range<double> particleSpeed;
	protected:
		Vector2d origin;
		std::vector<Particle> particles;
		double screenW, screenH;
		double camX, camY;
		double layerMultiplier;
		double spawnXOffset, spawnYOffset;

		virtual void onParticleDeath(Particle * particle) = 0;
		virtual void updateParticle(Particle * particle, double dt) = 0;
		virtual void onParticleSpawn(Particle * particle) = 0;
		virtual void onUpdate(double dt) = 0;

		virtual bool killCheck(Particle * particle);

		void spawnParticle(Particle * particle);
		void translateLocation(double worldX, double worldY, double & x, double & y);
	public:
		ParticleEffect(double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset);
		ParticleEffect * addParticleType(int id, double pct);

		virtual bool isActive();

		int getLayer();

		//Update the effect, killing off particles and other things. Called once every tick.
		bool update();
		//Render the particles on the screen.
		void render(SDL_Renderer * renderer, double deltaSeconds, double cameraX, double cameraY);
	};

}