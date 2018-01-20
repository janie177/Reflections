#include "PauseInputHandler.h"
#include "GameManager.h"

void reflections::PauseInputHandler::processKeyEvents(SDL_Event & input, GameManager * manager) {

	PauseMenu & pauseMenu = manager->getPauseMenu();
	Level * level = manager->getLevelManager().getCurrentLevel();

	switch (input.type) {
	case SDL_QUIT:
		manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (input.key.keysym.sym) {
		case SDLK_RIGHT:
		case SDLK_LEFT:
		case SDLK_a:
		case SDLK_d:
			pauseMenu.switchSelection();
			break;
		case SDLK_RETURN:
		case SDLK_ESCAPE:
			//Reset level to first level after game was won or lost.
			LevelState currentState = level->getLevelState();
			if (currentState == LevelState::LOSE || currentState == LevelState::WIN) {
				if (pauseMenu.getSelected() == MenuButton::CONTINUE) {
					manager->setGameState(MENU);
					level->setLevelState(LevelState::PLAYING);
					pauseMenu.reset();
				}
				else {
					manager->stop();
				}	
			}
			//If game is just paused, resume unless exit is selected and enter is pressed.
			else if (currentState == LevelState::PLAYING) {
				if (pauseMenu.getSelected() == MenuButton::CONTINUE || input.key.keysym.sym == SDLK_ESCAPE) {
					manager->setGameState(PLAYING);
				}
				else {
					manager->setGameState(MENU);
					level->setLevelState(LevelState::PLAYING);
				}
				pauseMenu.reset();
			}
			//Load the next level unless the player selects EXIT.
			else if (currentState == LevelState::NEXTLEVEL) {
				if (pauseMenu.getSelected() == MenuButton::EXIT) {
					manager->setGameState(MENU);
					level->setLevelState(LevelState::PLAYING);
				}
				else {
					manager->getLevelManager().loadLevel(manager->getLevelManager().getCurrentLevel()->getNextLevel());
					manager->setGameState(PLAYING);
				}
				pauseMenu.reset();
			}
			break;
		}
	}
}

void reflections::PauseInputHandler::processKeyStates(GameManager * manager, const Uint8 * state) {
}
