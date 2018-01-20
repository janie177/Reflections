#include "PlayingInputHandler.h"
#include "GameManager.h"
#include <iostream>

void reflections::PlayingInputHandler::processKeyEvents(SDL_Event & input, GameManager * manager) {

	switch (input.type) {
	case SDL_QUIT:
		manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (input.key.keysym.sym) {
			case SDLK_RETURN:
			case SDLK_ESCAPE:
				manager->setGameState(PAUSED);
				break;
			case SDLK_1:
				manager->getLevelManager().getCurrentLevel()->setCurrentWorld(0);
				break;
			case SDLK_2:
				manager->getLevelManager().getCurrentLevel()->setCurrentWorld(1);
				break;
		}
	}
}

void reflections::PlayingInputHandler::processKeyStates(GameManager * manager, const Uint8 * state) {
	Player & player = manager->getLevelManager().getCurrentLevel()->getPlayer();

	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_UP]) {
		player.jump();
	}

	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
		player.moveDown();
	}

	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
		player.moveLeft();
	}

	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
		player.moveRight();
	}
}
