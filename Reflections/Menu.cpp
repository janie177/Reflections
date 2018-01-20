#include "Menu.h"
#include "GameManager.h"

using namespace reflections;

reflections::Menu::Menu(GameManager * manager) {
	this->manager = manager;
	this->current = START;

	textureIDs[START] = 8002;
	selectedTextureIDs[START] = 8003;

	textureIDs[EXIT] = 8004;
	selectedTextureIDs[EXIT] = 8005;
}

MenuOption & reflections::Menu::getSelected() {
	return current;
}

void reflections::Menu::nextOption() {
	int value = current + 1;
	if (value >= 0 && value < MENU_OPTION_LENGTH) {
		current = (MenuOption) value;
	}
	else {
		current = (MenuOption) 0;
	}
}

void reflections::Menu::previousOption() {
	int value = current - 1;
	if (value >= 0 && value < MENU_OPTION_LENGTH) {
		current = (MenuOption) value;
	}
	else {
		current = (MenuOption) (MENU_OPTION_LENGTH - 1);
	}
}

void reflections::Menu::select() {
	switch (current) {
	case START:
		manager->getLevelManager().loadLevel(0);
		manager->setGameState(PLAYING);
		break;
	case EXIT:
		manager->stop();
		break;
	}
}

int reflections::Menu::getBackgroundID() {
	return 8001;
}

int reflections::Menu::getButtonHeight() {
	return 60;
}

int reflections::Menu::getButtonWidth() {
	return 240;
}

int reflections::Menu::getTopOffset() {
	return 300;
}

int reflections::Menu::getSpaceBetweenButtons() {
	return 30;
}

int reflections::Menu::getTextureID(MenuOption option) {
	return textureIDs[option];
}

int reflections::Menu::getSelectedTextureID(MenuOption option) {
	return selectedTextureIDs[option];
}
