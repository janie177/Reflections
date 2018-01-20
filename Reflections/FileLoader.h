#pragma once
#include <string>
#include "Level.h"
#include <cstdlib>
#include "FileReader.h"
#include "World.h"

namespace reflections {

	class LevelReader : public FileReader {
	private:
		Level * level;
	public:
		LevelReader(Level * level);
		bool readWorlds(std::vector<World*> & worlds);
	};
	
	//Fill a level with everything thats in its file.
	bool loadLevel(Level & level);
}