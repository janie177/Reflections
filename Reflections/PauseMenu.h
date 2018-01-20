#pragma once
#include <map>
#include "Text.h"
#include "Level.h"

namespace reflections {

	/*
	  Simple class for the Pause Menu.
	  Todo: create simple menu framework for some abstraction (Applies to Menu and PauseMenu).
	*/

	enum class MenuButton {
		CONTINUE,
		EXIT
	};

	class PauseMenu {
	private:
		MenuButton selectedButton;
		std::map<LevelState, Text*> textMap;
		std::map<MenuButton, int> textures;
		std::map<MenuButton, int> texturesSelected;
	public:
		PauseMenu();
		~PauseMenu();
		MenuButton getSelected();
		void switchSelection();
		Text * getText(LevelState state);
		int getTexture(MenuButton button);

		void reset();

		bool init();
	};
}