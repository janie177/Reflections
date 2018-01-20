#include "GUI.h"
#include "HealthElement.h"
#include "WorldsElement.h"

bool reflections::GUI::init() {
	elements[HEALTH] = (GUIElement*) new HealthElement();
	elements[WORLDS] = (GUIElement*) new WorldsElement();
	return true;
}

void reflections::GUI::render() {
	for (auto & element : elements) {
		if(element.second->isEnabled()) element.second->render();
	}
}

void reflections::GUI::destroy() {
	for (auto & element : elements) {
		delete element.second;
	}
	elements.clear();
}

//Turn GUI elements on or off. 
void reflections::GUI::setEnabled(ElementType type, bool enabled) {
	if (elements.count(type) > 0) {
		elements.at(type)->setEnabled(enabled);
	}
}
