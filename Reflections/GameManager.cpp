#include "GameManager.h"
#include "TextureManager.h"
#include <iostream>

using namespace reflections;

reflections::GameManager::GameManager() : gameTimer(60, 20), inputManager(this), menu(this), renderer(this) {
	this->gameState = MENU;
	this->running = true;
}

GameManager & reflections::GameManager::getInstance() {
	static GameManager instance;
	return instance;
}

bool reflections::GameManager::init() {
	return renderer.init() && TextureManager::loadTextures() && TileType::init() && gui.init() && pauseMenu.init();
}

Renderer & reflections::GameManager::getRenderer() {
	return renderer;
}

LevelManager & reflections::GameManager::getLevelManager() {
	return levelManager;
}

GameTimer & reflections::GameManager::getGameTimer() {
	return gameTimer;
}

GameState & reflections::GameManager::getGameState() {
	return gameState;
}

InputManager & reflections::GameManager::getInputManager() {
	return inputManager;
}

GUI & reflections::GameManager::getGUI() {
	return gui;
}

Menu & reflections::GameManager::getMenu() {
	return menu;
}

PauseMenu & reflections::GameManager::getPauseMenu() {
	return pauseMenu;
}

bool reflections::GameManager::isRunning() {
	return running;
}

void reflections::GameManager::stop() {
	running = false;
}

void reflections::GameManager::destroy() {
	TextureManager::destroy();

	//Destroy created GUi objects.
	gui.destroy();

	//Delete loaded levels.
	levelManager.destroy();

	//Free texture memory
	TextureManager::destroy();

	//Free tile memory
	TileType::destroy();

	//Destroy rendering context
	renderer.quit();
}

void reflections::GameManager::setGameState(GameState state) {
	this->gameState = state;
}
