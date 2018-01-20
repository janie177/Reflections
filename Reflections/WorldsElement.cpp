#include "WorldsElement.h"
#include "GameManager.h"
#include <iostream>

using namespace reflections;

reflections::WorldsElement::WorldsElement() : GUIElement(WORLDS, 3, 3){
}

void reflections::WorldsElement::renderElement() {
	int i, lastWorldX;
	Renderer & renderer = GameManager::getInstance().getRenderer();
	Level * currentLevel = GameManager::getInstance().getLevelManager().getCurrentLevel();
	World * world = nullptr;
	Texture * texture = nullptr;
	Text * text = nullptr;

	for (i = 0; i < currentLevel->getWorldCount(); i++) {
		world = currentLevel->getWorld(i);
		if (world != nullptr) {
			texture = TextureManager::getTexture(world->getIconID());
			text = world->getName();

			//Indicate which world is currently selected.
			if (world == &(currentLevel->getCurrentWorld())) {
				SDL_SetTextureAlphaMod(texture->getTexture(), 255);
			}
			else {
				SDL_SetTextureAlphaMod(texture->getTexture(), 100);
			}

			rectangle.w = texture->getWidth();
			rectangle.h = texture->getHeight();

			SDL_RenderCopy(renderer.getRenderer(), texture->getTexture(), NULL, &rectangle);
			rectangle.y += texture->getHeight() + 2;

			rectangle.w = text->getWidth();
			rectangle.h = text->getHeight();

			lastWorldX = rectangle.x;
			rectangle.x += (texture->getFrameWidth() / 2) - (text->getWidth() / 2);
			SDL_RenderCopy(renderer.getRenderer(), text->getTexture(), NULL, &rectangle);

			rectangle.x = lastWorldX;
			rectangle.x += texture->getWidth() + 4;
			rectangle.y = originalY;
		}
	}
}
