#include "MenuInputHandler.h"
#include "GameManager.h"

void reflections::MenuInputHandler::processKeyEvents(SDL_Event & input, GameManager * manager) {

	switch (input.type) {
	case SDL_QUIT:
		manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (input.key.keysym.sym) {
		case SDLK_DOWN:
		case SDLK_s:
			manager->getMenu().nextOption();
			break;
		case SDLK_UP:
		case SDLK_w:
			manager->getMenu().previousOption();
			break;
		case SDLK_RETURN:
			manager->getMenu().select();
			break;
		}
		break;
	}
}

void reflections::MenuInputHandler::processKeyStates(GameManager * manager, const Uint8 * state) {
}
