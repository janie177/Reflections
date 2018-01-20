#include "HealthElement.h"
#include "GameManager.h"
#include <SDL.h>
#include "TextureManager.h"

using namespace reflections;

reflections::HealthElement::HealthElement() : GUIElement(HEALTH, 84, 3) {
	texture = TextureManager::getTexture(100001);
	playerIcon = TextureManager::getTexture(100002);
	rectangle.w = texture->getWidth();
	rectangle.h = texture->getHeight();
}

void reflections::HealthElement::renderElement() {
	int i;
	Renderer & renderer = GameManager::getInstance().getRenderer();
	Player & player = GameManager::getInstance().getLevelManager().getCurrentLevel()->getPlayer();

	rectangle.w = playerIcon->getWidth();
	rectangle.h = playerIcon->getHeight();

	SDL_RenderCopy(renderer.getRenderer(), playerIcon->getTexture(), NULL, &rectangle);
	rectangle.x += playerIcon->getWidth() + 10;

	rectangle.w = texture->getWidth();
	rectangle.h = texture->getHeight();

	for (i = 0; i < player.getHealth(); i++) {
		SDL_RenderCopy(renderer.getRenderer(), texture->getTexture(), NULL, &rectangle);
		rectangle.x += texture->getWidth() + 2;
	}
}
