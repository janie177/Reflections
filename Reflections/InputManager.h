#pragma once
#include <map>

namespace reflections {

	class GameManager;
	class InputHandler;
	enum GameState;

	class InputManager {
	private:
		std::map<GameState, InputHandler*> handlers;
		GameManager * gameManager;
		bool blockInput;
	public:
		InputManager(GameManager * gameManager);
		void processInput();
		void setBlockInput(bool block);
		void init();
	};
}