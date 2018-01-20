#pragma once
#include <vector>
#include <SDL.h>

namespace reflections {

	enum ElementType {
		HEALTH, WORLDS
	};

	class GUIElement {
	private:
		ElementType type;
		bool enabled;
	protected:
		double screenXPct;
		double screenYPct;
		double originalX, originalY;
		SDL_Rect rectangle;
	public:
		GUIElement(ElementType type, double screenXPct, double screenYPct);
		ElementType getType();
		void render();
		virtual void renderElement() = 0;
		void setEnabled(bool enabled);
		bool isEnabled();
	};
}