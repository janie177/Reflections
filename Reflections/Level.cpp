#include "Level.h"
#include "FileLoader.h"
#include "EntityManager.h"
#include "GameManager.h"

using namespace reflections;

reflections::Level::Level() {
	currentState = LevelState::PLAYING;
	this->player = nullptr;
	this->currentWorld = nullptr;
	this->startX = 0;
	this->startY = 0;
}

//Call destroy method when level is discarded.
reflections::Level::~Level() {
	destroy();
}

//Load all data from the file at the given path.
bool reflections::Level::load() {

	//If level failed to load, return false.
	if (!loadLevel(*this)) {
		return false;
	}

	//Have each level set their startX and startY.
	setStartLocation(startX, startY);

	currentWorld = worlds.at(0);

	//Create player object and set the start location.
	player = (Player*) getCurrentWorld().createEntity(PLAYER);
	camera = (Camera*) getCurrentWorld().createEntity(CAMERA);

	Location start = player->getLocation().set(startX, startY);
	player->setLocation(start);
	camera->setLocation(start);

	//Reset level state for when the same level is played twice (After dying).
	currentState = LevelState::PLAYING;
	return true;
}

//Destroy all objects inside the level (Worlds, Chunks, Tiles, Player, Camera).
bool reflections::Level::destroy() {
	int i;
	try {
		//Call the destroy method for each world.
		for (i = 0; i < worlds.size(); i++) {
			worlds[i]->destroy();
		}
		player = nullptr;
		camera = nullptr;
		currentWorld = nullptr;
		worlds.clear();
	}
	catch (...) {
		return false;
	}
	return true;
}

Player & reflections::Level::getPlayer() {
	return *player;
}

Camera & reflections::Level::getCamera() {
	return *camera;
}

void reflections::Level::setLevelState(LevelState state) {
	this->currentState = state;
}

LevelState reflections::Level::getLevelState() {
	return currentState;
}

double reflections::Level::getStartX() {
	return startX;
}

double reflections::Level::getStartY() {
	return startY;
}

int reflections::Level::getWorldCount() {
	return worlds.size();
}

World * reflections::Level::getWorld(int index) {
	if (worlds.size() <= index) {
		return nullptr;
	}
	return worlds.at(index);
}

//Get a refference to the current world.
World & reflections::Level::getCurrentWorld() {
	return *currentWorld;
}

//Set the current world to a specific index, if the index is valid.
//NOTE: This is a design flaw. Switching the world from inside the world update tick loop would cause the game to crash under the right conditions.
bool reflections::Level::setCurrentWorld(int index) {
	int worldSize = worlds.size();
	if (index < worldSize && index > -1) {
		World * oldWorld = currentWorld;
		World * newWorld = getWorld(index);

		if (newWorld != nullptr && oldWorld != newWorld && player != nullptr) {

			int lastTP = player->getLastTeleport();
			int tick = GameManager::getInstance().getGameTimer().getTick();

			if (tick - lastTP > PLAYER_TELEPORT_COOLDOWN) {
				player->setLastTeleport(tick);
				player->setLocation(player->getLocation().setWorld(*newWorld));
				player->getTextureData().setTexture(2001);

				//Update entity queues for old and new world. 
				//This prevents memory access violations when entities in a world are being edited as the player switches world.
				currentWorld->applyEntityQueues();
				currentWorld = newWorld;
				currentWorld->applyEntityQueues();

				Location playerLoc = player->getLocation();
				currentWorld->createParticleEffect(CLOUD, playerLoc.getX(), playerLoc.getY() + 40, 2, 1200, 0, 60, 60, 9999, 2.0, 0.5, 0.8, 50, 150, 3, 3)->addParticleType(4012, 100);
			}
		}
		return true;
	}
	return false;
}
