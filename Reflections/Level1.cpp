#include "Level1.h"
#include "TextEntity.h"
#include "Tile.h"
#include <algorithm>

using namespace reflections;

std::string reflections::Level1::getPath() {
	return "Assets/Levels/Level1.dat";
}

void reflections::Level1::onStart() {
	int i, id;
	std::vector<int> lava;
	lava.push_back(11);
	lava.push_back(12);
	lava.push_back(13);
	lava.push_back(14);
	lava.push_back(15);
	lava.push_back(16);

	//Fill world with grass, stone and lava
	for (i = 0; i < 60; i++) {
		getCurrentWorld().addTile(new Tile(64 * i, 0, getCurrentWorld(), *TileType::typeFromID(0)));

		if(std::find(lava.begin(), lava.end(), i) != lava.end()) {
			getWorld(1)->addTile(new Tile(64 * i, -10, *getWorld(1), *TileType::typeFromID(1)));
			getWorld(1)->addParticleEffect(ParticleManager::create(FOUNTAIN, 64 * i, 54, 2, 2000, 150, 14, 0, 5, 0, 1, 3, 10, 30, 32, 0)->addParticleType(4011, 70)->addParticleType(4003, 30));
		}
		else {
			getWorld(1)->addTile(new Tile(64 * i, 0, *getWorld(1), *TileType::typeFromID(3)));
		}
	}
	

	/*
		Particle effect for lanterns
	*/
	getWorld(0)->addParticleEffect(ParticleManager::create(DRIP, 150, 265, 2, 2000, 160, 30, 0, 2, 0, 3, 9, 6, 22, 5, 3)->addParticleType(4002, 50)->addParticleType(4003, 50));
	getWorld(0)->addParticleEffect(ParticleManager::create(DRIP, 650, 265, 2, 2000, 160, 30, 0, 2, 0, 3, 9, 6, 22, 5, 3)->addParticleType(4002, 50)->addParticleType(4003, 50));
	getWorld(0)->addParticleEffect(ParticleManager::create(DRIP, 1150, 265, 2, 2000, 160, 30, 0, 2, 0, 3, 9, 6, 22, 5, 3)->addParticleType(4002, 50)->addParticleType(4003, 50));

	/*
		Particle effect for lava vents.
	*/
	getWorld(1)->addParticleEffect(ParticleManager::create(RISING, 300, 90, 2, 2000, 240, 50, 0, 15, 0, 3, 12, 30, 60, 15, 3)->addParticleType(4003, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RISING, 500, 90, 2, 2000, 240, 50, 0, 15, 0, 3, 12, 30, 60, 15, 3)->addParticleType(4003, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RISING, 564, 90, 2, 2000, 240, 50, 0, 15, 0, 3, 12, 30, 60, 15, 3)->addParticleType(4003, 100));

	/*
		AIR PARTICLES IN PRESENT
	*/
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 0, 0, 0, 12, 0, 12, 0, 0, 0, 1, 2, 3, 3)->addParticleType(4004, 100));
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 1, 0, 0, 15, 0, 15, 0, 0, 0, 2, 4, 3, 3)->addParticleType(4004, 100));
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 2, 0, 0, 20, 0, 20, 0, 0, 0, 7, 10, 3, 3)->addParticleType(4001, 25)->addParticleType(4003, 75));
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 3, 0, 0, 15, 0, 15, 0, 0, 0, 14, 20, 3, 3)->addParticleType(4005, 100));

	/*
		RAIN
	*/
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 0, 0, 0, 50, 0, 70, 0, 0, 0, 200, 300, 3, 3)->addParticleType(4009, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 1, 0, 0, 60, 0, 100, 0, 0, 0, 300, 420, 3, 3)->addParticleType(4009, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 2, 0, 0, 70, 0, 150, 0, 0, 0, 400, 500, 3, 3)->addParticleType(4009, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 3, 0, 0, 80, 0, 50, 0, 0, 0, 700, 810, 3, 3)->addParticleType(4008, 100));
}

void reflections::Level1::update() {
	getCurrentWorld().updateTick();
}

void reflections::Level1::onEnd() {
}

int reflections::Level1::getNextLevel() {
	return 0;
}

void reflections::Level1::setStartLocation(double & startX, double & startY) {
	startX = 100;
	startY = 80;
}
