#pragma once
#include "Entity.h"
#include <string>
#include <vector>
#include "Text.h"

namespace reflections {

	//TextEntity is an entity that allows text to be rendered in the world.
	//This can be used for instructions, name tags, damage display and other text that has to be rendered inside the game world.
	class TextEntity : public Entity {
	private:
		std::vector<Text*> text;
	public:
		TextEntity(World & world);
		
		TextEntity * addText(std::string str, int r, int g, int b);
		Text * getText(int index);
		void removeText(int index);

		std::vector<Text*> & getText();

		~TextEntity();
	};
}


