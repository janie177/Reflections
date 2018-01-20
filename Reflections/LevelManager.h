#pragma once
#include "Level.h"
#include <map>

/*
	LevelManager is the file that handles level loading and initiating.
	When I first started on the game, I designed it so that all level data is loaded from a .dat file.
	The file contained player texture, background texture IDs, tiles, entities and a string which determined the next level.

	While this made level creation and loading completely dynamic, it only allowed basic level design.
	I could not create too much custom stuff in a level because it would have to all be config-based.
	This is why I decided to create a LevelManager and give levels an ID.

	Using abstraction, I can actually hardcode specific features for each level now. Levels are not entirely dynamic, but they are completely customizable now.

	Levels still load their tiles and entities from file because they form the basics of a level. Only exceptions will be hard coded.
*/


namespace reflections {

	//Level manager class which is used to handle levels
	class LevelManager {
	private:
		std::map<int, Level*> levelMap;
		Level * currentLevel;
	public:
		LevelManager();

		Level * getCurrentLevel();
		bool loadLevel(int id);

		void init();
		void destroy();
	};
}