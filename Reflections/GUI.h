#pragma once
#include <map>
#include "GUIElement.h"


namespace reflections {

	class GUI {
	private:
		std::map<ElementType, GUIElement*> elements;
	public:
		bool init();
		void render();
		void destroy();
		void setEnabled(ElementType type, bool enabled);
	};
}