#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "Renderer.h"
#include "Texture.h"
#include "Level.h"
#include "GameManager.h"

using namespace reflections;

int reflections::run() {

	//Reference to the game manager.
	GameManager & manager = GameManager::getInstance();

	while (manager.isRunning()) {

		//Update the timer to the current time.
		manager.getGameTimer().update();

		//Update everything in the game if enough time has passed.
		if (manager.getGameTimer().nextTick()) {
			//Update input.
			manager.getInputManager().processInput();

			//If the current level is not null, process user input and then update the rest of the world.
			if (manager.getGameState() == PLAYING && manager.getLevelManager().getCurrentLevel() != nullptr) {
				//Update all TileType textures
				TileType::updateTextureData();
				//Update level
				manager.getLevelManager().getCurrentLevel()->update();
				//std::cout << "FPS: " << manager.getGameTimer().getActualFPS() << " TPS: " << manager.getGameTimer().getActualTPS() << std::endl;
			}
		}

		//Check for new frame
		if (manager.getGameTimer().nextFrame()) {
			manager.getRenderer().render();
		}
	}

	return 0;
}
