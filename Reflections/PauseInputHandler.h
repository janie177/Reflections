#pragma once
#include "InputHandler.h"

namespace reflections {

	class PauseInputHandler : public InputHandler {
	public:
		void processKeyEvents(SDL_Event & input, GameManager * manager);
		void processKeyStates(GameManager * manager, const Uint8 * state);
	};
}