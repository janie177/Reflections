#pragma once
#include <string>

#define MENU_OPTION_LENGTH 2

namespace reflections {

	class GameManager;

	enum MenuOption {
		START,
		EXIT
	};

	class Menu {
	private:
		GameManager * manager;
		MenuOption current;
		int textureIDs[MENU_OPTION_LENGTH];
		int selectedTextureIDs[MENU_OPTION_LENGTH];

	public:
		Menu(GameManager * manager);
		MenuOption & getSelected();
		void nextOption();
		void previousOption();

		void select();

		int getBackgroundID();
		int getButtonHeight();
		int getButtonWidth();

		int getTopOffset();
		int getSpaceBetweenButtons();

		int getTextureID(MenuOption option);
		int getSelectedTextureID(MenuOption option);
	};
}