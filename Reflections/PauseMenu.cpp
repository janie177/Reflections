#include "PauseMenu.h"
#include <iostream>

using namespace reflections;

reflections::PauseMenu::PauseMenu() {

}

reflections::PauseMenu::~PauseMenu() {
	std::map<LevelState, Text*>::iterator it = textMap.begin();
	while (it != textMap.end()) {
		it->second->destroy();
		it++;
	}
	textMap.clear();
	textures.clear();
	texturesSelected.clear();
}

MenuButton reflections::PauseMenu::getSelected() {
	return selectedButton;
}

void reflections::PauseMenu::switchSelection() {
	if (selectedButton == MenuButton::CONTINUE) {
		selectedButton = MenuButton::EXIT;
	}
	else {
		selectedButton = MenuButton::CONTINUE;
	}
}

Text * reflections::PauseMenu::getText(LevelState state) {
	return textMap[state];
}

int reflections::PauseMenu::getTexture(MenuButton button) {
	if (button == selectedButton) {
		return texturesSelected[button];
	}
	return textures[button];
}

void reflections::PauseMenu::reset() {
	selectedButton = MenuButton::CONTINUE;
}

bool reflections::PauseMenu::init() {
	selectedButton = MenuButton::CONTINUE;

	textMap[LevelState::PLAYING] = Text::create("Paused", 255, 255, 255)->scale(7);
	textMap[LevelState::NEXTLEVEL] = Text::create("Level Complete!", 0, 255, 0)->scale(5);
	textMap[LevelState::WIN] = Text::create("Game Complete!", 0, 255, 0)->scale(4);
	textMap[LevelState::LOSE] = Text::create("Game Over", 255, 0, 0)->scale(6);

	textures[MenuButton::CONTINUE] = 8006;
	texturesSelected[MenuButton::CONTINUE] = 8007;
	textures[MenuButton::EXIT] = 8004;
	texturesSelected[MenuButton::EXIT] = 8005;
	return true;
}
