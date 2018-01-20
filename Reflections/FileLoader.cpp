#include <iostream>
#include "FileLoader.h"
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include "Texture.h"
#include "EntityManager.h"
#include "Tile.h"

using namespace reflections;

bool reflections::loadLevel(Level & level) {
	//Create a LevelReader to handle the level file.
	LevelReader reader(&level);

	if (!reader.open()) {
		std::cout << "Could not open level file: " << level.getPath() << "." << std::endl;
		return false;
	}

	//Put this in a try/catch because you never know what can be in a level file.
	try {
		if (!reader.readWorlds(level.worlds)) {
			std::cout << "Could not parse level file: " << level.getPath() << "." << std::endl;
			return false;
		}
	}
	catch (...) {
		std::cout << "Could not parse level file: " << level.getPath() << "." << std::endl;
		return false;
	}

	reader.close();
	return true;
}

//Methods belonging to level reader.

reflections::LevelReader::LevelReader(Level * level) : FileReader(level->getPath()) {
	this->level = level;
}

//This method will loop through the file multiple times to find all worlds and their required data
bool reflections::LevelReader::readWorlds(std::vector<World*> & worlds) {

	//Vectors containing the starting positions of each section for each world.
	int worldSize = 0;
	int i;
	std::vector<int> backgroundStarts;
	std::vector<int> tileStarts;
	std::vector<int> entityStarts;
	std::vector<int> dataStarts;

	//First iteration, locate all "world:" tags and save where each section starts.
	while (nextLine()) {
		if (getCurrentLine().compare("world:") == 0) {
			worldSize++;
		}
		else if (getCurrentLine().compare("background:") == 0) {
			backgroundStarts.push_back(getPos());
		}
		else if (getCurrentLine().compare("tiles:") == 0) {
			tileStarts.push_back(getPos());
		}
		else if (getCurrentLine().compare("entities:") == 0) {
			entityStarts.push_back(getPos());
		}
		else if (getCurrentLine().compare("data:") == 0) {
			dataStarts.push_back(getPos());
		}
	}

	//Check if each world contains all the needed info. If there's no worlds or a world misses a section, return false.
	if (worldSize < 1 || backgroundStarts.size() != worldSize || tileStarts.size() != worldSize || tileStarts.size() != worldSize || 
		entityStarts.size() != worldSize || dataStarts.size() != worldSize) {
		return false;
	}

	//For every world, create a new world object and then load in the data from the corresponding sections in the file.
	//Use try catch in case the input isn't right.
	try {

		std::string name;
		int iconID;

		//Get the worlds extra data.
		for (i = 0; i < worldSize; i++) {
			//Get the name of the world
			setPos(*(dataStarts.begin() + i));
			while (nextLine() && getCurrentLine().c_str()[0] == '-') {
				int b1, b2, b3, b4;
				std::string line = getCurrentLine();
				line.erase(0, 1);
				std::replace(line.begin(), line.end(), ',', ' ');
				std::stringstream stream(line);
				stream >> name >> iconID;
			}

			
			//Create a new world object to store in the level.
			World * world = new World(level, name, iconID);
		
			//Background
			setPos(*(backgroundStarts.begin()+i));
			while (nextLine() && getCurrentLine().c_str()[0] == '-') {
				int b1, b2, b3, b4;
				std::string line = getCurrentLine();
				line.erase(0, 1);
				std::replace(line.begin(), line.end(), ',', ' ');
				std::stringstream stream(line);
				stream >> b1 >> b2 >> b3 >> b4;

				//Set the worlds background to the three texture ID's.
				world->setBackground(b1, b2, b3, b4);
			}

			//Entities
			setPos(*(entityStarts.begin() + i));
			while (nextLine() && getCurrentLine().c_str()[0] == '-') {
				int id;
				int x, y;
				std::string line = getCurrentLine();
				line.erase(0, 1);
				std::replace(line.begin(), line.end(), ',', ' ');
				std::stringstream stream(line);
				stream >> id >> x >> y;

				//Create a new Entity and add it to the world.
				//Cast the ID to EntityType.
				Entity * entity = EntityManager::createEntity(id, *world);
				if (entity != nullptr) {
					entity->setLocation(entity->getLocation().set(x, y));
					world->addEntity(entity);
				}
			}

			//Tiles
			setPos(*(tileStarts.begin() + i));
			while (nextLine() && getCurrentLine().c_str()[0] == '-') {
				int id, x, y;
				std::string line = getCurrentLine();
				line.erase(0, 1);
				std::replace(line.begin(), line.end(), ',', ' ');
				std::stringstream stream(line);
				stream >> id >> x >> y;

				TileType * type = TileType::typeFromID(id);

				if (type != nullptr) {
					//Create a new tile and add it to the world.
					Tile * tile = new Tile(x, y, *world, *type);
					world->addTile(tile);
				}
				else {
					std::cout << "Error loading tile with ID: " << id << " in level " << level->getPath() << "." << std::endl;
				}
			}

			//Add the world to the level.
			worlds.push_back(world);
		}
	}
	catch (...) {
		std::cout << "Error occured while loading world in level." << std::endl;
		return false;
	}
	
	//Finally, restore the file once more and return true.
	rewind();
	return true;
}