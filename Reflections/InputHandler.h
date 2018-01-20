#pragma once
#include <SDL_events.h>

namespace reflections {

	//Forward delcaration
	class GameManager;

	class InputHandler {
	public:
		virtual void processKeyEvents(SDL_Event & input, GameManager * manager) = 0;
		virtual void processKeyStates(GameManager * manager, const Uint8 * state) = 0;
	};
}