#include <iostream>
#include "LevelManager.h"
#include "Tutorial.h"
#include "Level1.h"

using namespace reflections;

reflections::LevelManager::LevelManager() {
	this->currentLevel = nullptr;
	init();
}

Level * reflections::LevelManager::getCurrentLevel() {
	return currentLevel;
}

bool reflections::LevelManager::loadLevel(int id) {

	//Destroy old level. Free all memory again.
	if (currentLevel != nullptr) {
		currentLevel->destroy();
		currentLevel = nullptr;
	}

	//Make sure level ID is found.
	if (levelMap.count(id) != 1) {
		std::cout << "Could not find level with id: " << id << "." << std::endl;
		return false;
	}

	//Set level as current.
	currentLevel = levelMap[id];
	//Make sure the level doesn't fail to load the tiles and entities
	if (!currentLevel->load()) {
		std::cout << "Could not load level with id: " << id << "." << std::endl;
		currentLevel = nullptr;
		return false;
	}

	//Call the onStart() method to init any custom things.
	currentLevel->onStart();

	//Level loaded, return true.
	return true;
}

//Static method that puts all level instances in the map that is used to load them.
void reflections::LevelManager::init() {
	levelMap[0] = (Level*) new Tutorial();
	levelMap[1] = (Level*) new Level1();
}

void reflections::LevelManager::destroy() {
	if (currentLevel != nullptr) {
		currentLevel->destroy();
		currentLevel = nullptr;
	}
	for (auto & level : levelMap) {
		delete level.second;
	}
}
