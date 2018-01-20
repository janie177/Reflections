#include "InputManager.h"
#include "GameState.h"
#include "GameManager.h"
#include <SDL_events.h>
#include "PlayingInputHandler.h"
#include "MenuInputHandler.h"
#include "PauseInputHandler.h"
#include <iostream>

using namespace reflections;

//Fill the map with the handlers for each game state.
reflections::InputManager::InputManager(GameManager * gameManager) {
	this->gameManager = gameManager;
	blockInput = false;
	init();
}

//Process the input for the current gamestate.
//NOTE: input is an SDL event. That means it is only fired when a key is pressed or released or other changes in behaviour happen.
//keyState is a pointer to an array containing the actual key states. USe this for real-time input instead of waiting for an event.
//Example: Holding W first fires a W press event, then it waits a second before firing multiple events because the key starts repeating.
//The keyState array will not have such an interuption and will always return true as long as W is pressed.
void reflections::InputManager::processInput() {
	static const Uint8 * keyState = SDL_GetKeyboardState(NULL);
	static SDL_Event input;

	//Process all key events if present.
	while (SDL_PollEvent(&input) != 0) {
		if (!blockInput) {
			handlers[gameManager->getGameState()]->processKeyEvents(input, gameManager);
		}
	}

	//Check against current keyboard state.
	if (!blockInput) {
		handlers[gameManager->getGameState()]->processKeyStates(gameManager, keyState);
	}
}

void reflections::InputManager::setBlockInput(bool block) {
	blockInput = block;
}

void reflections::InputManager::init() {
	handlers[PLAYING] = new PlayingInputHandler();
	handlers[MENU] = new MenuInputHandler();
	handlers[PAUSED] = new PauseInputHandler();
}
