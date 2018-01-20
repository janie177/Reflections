#include "GUIElement.h"
#include <SDL.h>
#include "GameManager.h"

using namespace reflections;

reflections::GUIElement::GUIElement(ElementType type, double screenXPct, double screenYPct) {
	this->type = type;
	this->screenXPct = screenXPct;
	this->screenYPct = screenYPct;
	enabled = true;

	Renderer & renderer = GameManager::getInstance().getRenderer();
	rectangle.x = (renderer.getScreenWidth() / 100) * screenXPct;
	rectangle.y = (renderer.getScreenHeight() / 100) * screenYPct;
	originalX = rectangle.x;
	originalY = rectangle.y;
}
ElementType reflections::GUIElement::getType() {
	return type;
}

void reflections::GUIElement::render() {
	rectangle.x = originalX;
	rectangle.y = originalY;
	renderElement();
}

void reflections::GUIElement::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool reflections::GUIElement::isEnabled() {
	return enabled;
}
