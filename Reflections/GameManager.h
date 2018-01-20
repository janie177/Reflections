#pragma once
#include "GameTimer.h"
#include "GameState.h"
#include "InputManager.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "LevelManager.h"
#include "Renderer.h"
#include "GUI.h"

namespace reflections {

	//GameManager is the class that contains all relevant info of the game.
	//It is a singleton and thus has only a single instance.
	class GameManager {
	private:
		Renderer renderer;
		LevelManager levelManager;
		GameTimer gameTimer;
		InputManager inputManager;
		GameState gameState;
		Menu menu;
		PauseMenu pauseMenu;
		GUI gui;
		bool running;
		GameManager();
	public:
		//Get singleton instance.
		static GameManager & getInstance();

		//Delete methods so no extra instances can ever be created.
		GameManager(GameManager const&) = delete;
		void operator=(GameManager const&) = delete;

		//Init separate sub-systems.
		bool init();

		Renderer & getRenderer();
		LevelManager & getLevelManager();
		GameTimer & getGameTimer();
		GameState & getGameState();
		InputManager & getInputManager();
		GUI & getGUI();
		Menu & getMenu();
		PauseMenu & getPauseMenu();


		bool isRunning();

		void stop();

		void destroy();

		void setGameState(GameState state);

	};
}