#include "Tutorial.h"
#include "TextEntity.h"
#include "World.h"
#include <iostream>
#include "ParticleManager.h"
#include "Tile.h"

using namespace reflections;

std::string reflections::Tutorial::getPath() {
	return "Assets/Levels/Tutorial.dat";
}

void reflections::Tutorial::onStart() {
	TextEntity * text;

	/*
		Tutorial related text in the world
	*/

	((TextEntity*)getCurrentWorld().createEntity(TEXT))->addText("Lava is dangerous!", 255, 15, 15)->addText("Touching it is a bad idea.", 255, 255, 255)->setLocation(990, 200);

	text = (TextEntity*) getCurrentWorld().createEntity(TEXT);
	text->addText("This is the tutorial!", 255, 255, 255);
	text->addText("Use WASD to move.", 255, 155, 155);
	text->addText("Press [Space] or [W] to jump.", 155, 15, 200);
	text->setLocation(text->getLocation().set(400, 200));

	text = (TextEntity*)getCurrentWorld().createEntity(TEXT);
	text->addText("Lava is dangerous!", 255, 15, 15);
	text->addText("Touching it is a bad idea.", 255, 255, 255);
	text->setLocation(text->getLocation().set(990, 200));

	text = (TextEntity*)getCurrentWorld().createEntity(TEXT);
	text->addText("Switch between timelines:", 200, 200, 200);
	text->getText(0)->scale(1.5);
	text->addText("[1] The future", 0,160,0);
	text->addText("[2] The past", 100,30,30);
	text->setLocation(text->getLocation().set(1400, 500));

	text = (TextEntity*)getWorld(1)->createEntity(TEXT);
	text->addText("Tip:", 255, 15, 155);
	text->addText("Time only flows", 255, 255, 255);
	text->addText("in your current timeline!", 255, 255, 255);
	text->setLocation(text->getLocation().set(990, 400));

	text = (TextEntity*)getWorld(1)->createEntity(TEXT);
	text->addText("Touch the flag!", 100, 255, 100);
	text->addText("Flags mark the end", 255, 255, 255);
	text->addText("of a level.", 255, 255, 255);
	text->setLocation(text->getLocation().set(1800, 280));

	text = (TextEntity*)getWorld(1)->createEntity(TEXT);
	text->addText("Watch out!", 255, 100, 100);
	text->addText("These plants spit", 50,100,50);
	text->addText("goo at you.", 50,100,50);
	text->setLocation(text->getLocation().set(2200, 540));

	//Fill world with grass and stone
	for (int i = 0; i < 15; i++) {
		getCurrentWorld().addTile(new Tile(64 * i, 0, getCurrentWorld(), *TileType::typeFromID(0)));
		getWorld(1)->addTile(new Tile(64 * i, 0, *getWorld(1), *TileType::typeFromID(3)));
	}

	for (int i = 17; i < 37; i++) {
		getCurrentWorld().addTile(new Tile(64 * i, 0, getCurrentWorld(), *TileType::typeFromID(0)));
		getWorld(1)->addTile(new Tile(64 * i, 0, *getWorld(1), *TileType::typeFromID(3)));
	}


	/*
		AIR PARTICLES IN PRESENT
	*/
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 0, 0, 0, 12, 0, 12, 0, 0, 0, 1, 2, 3, 3)->addParticleType(4004, 100));
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 1, 0, 0, 15, 0, 15, 0, 0, 0, 2, 4, 3, 3)->addParticleType(4004, 100));
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 2, 0, 0, 20, 0, 20, 0, 0, 0, 7, 10, 3, 3)->addParticleType(4001, 25)->addParticleType(4003,75));
	getCurrentWorld().addParticleEffect(ParticleManager::create(AEROSOLS, 0, 0, 3, 0, 0, 15, 0, 15, 0, 0, 0, 14, 20, 3, 3)->addParticleType(4005, 100));

	/*
		ASH RAIN IN PAST
	*/
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 0, 0, 0, 70, 0, 70, 0, 0, 0, 20, 35, 3, 3)->addParticleType(4001, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 1, 0, 0, 100, 0, 100, 0, 0, 0, 35, 50, 3, 3)->addParticleType(4001, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 2, 0, 0, 150, 0, 150, 0, 0, 0, 70, 90, 3, 3)->addParticleType(4001, 100));
	getWorld(1)->addParticleEffect(ParticleManager::create(RAIN, 0, 0, 3, 0, 0, 50, 0, 50, 0, 0, 0, 150, 200, 3, 3)->addParticleType(4001, 100));


	/*
		Lava fire fountain
	*/

	getWorld(0)->addParticleEffect(ParticleManager::create(FOUNTAIN, 960, 50, 2, 2000, 150, 100, 0, 20, 0, 1, 3, 15, 30, 32, 5)->addParticleType(4003, 40));
	getWorld(0)->addParticleEffect(ParticleManager::create(FOUNTAIN, 1024, 50, 2, 2000, 150, 100, 0, 20, 0, 1, 3, 15, 30, 32, 5)->addParticleType(4003, 40));

	/* 
	effect = ParticleManager::create(FOUNTAIN, 2000, 200, 1, 500, 150, 100, 0, 15, 0, 0, 0, 20, 60, 3, 3);
	effect->addParticleType(4001, 25);
	effect->addParticleType(4002, 25);
	effect->addParticleType(4003, 25);
	effect->addParticleType(4004, 25);
	getCurrentWorld().addParticleEffect(effect);

	effect = ParticleManager::create(FOUNTAIN, 400, 200, 2, 500, 150, 100, 0, 20, 0, 0, 0, 25, 50, 100, 50);
	effect->addParticleType(4002, 100);
	getCurrentWorld().addParticleEffect(effect);
	*/
}

void reflections::Tutorial::update() {
	getCurrentWorld().updateTick();
}

void reflections::Tutorial::onEnd() {
}

int reflections::Tutorial::getNextLevel() {
	return 1;
}

void reflections::Tutorial::setStartLocation(double & startX, double & startY) {
	startX = 64;
	startY = 64;
}
