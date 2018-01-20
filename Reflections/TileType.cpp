#include "TileType.h"
#include <map>

using namespace reflections;

//Static definition of registry map.
std::map<int, TileType*> TileType::registry;

//Definitions of constructors and functions.
TileType::TileType(int id, int textureID, bool solid, int width, int height, double hitBoxW, double hitBoxH) : Textured(textureID) {
	this->id = id;
	this->type = (TypeName)id;
	this->width = width;
	this->height = height;
	this->solid = solid;
	this->hitBoxH = hitBoxH;
	this->hitBoxW = hitBoxW;

	//After setting all the data, add it to the map containing each type sorted by ID.
	registry[id] = this;
}

//Constructor delegating to allow default hitbox widh and height
TileType::TileType(int id, int textureID, bool solid, int width, int height) : TileType(id, textureID, solid, width, height, width, height) {}

TileType::~TileType() {
	//Remove entry from the map if type no longer has a value.
	registry.erase(id);
}

int TileType::getID() {
	return id;
}

int TileType::getWidth() {
	return width;
}

int TileType::getHeight() {
	return height;
}

bool TileType::isSolid() {
	return solid;
}

TypeName reflections::TileType::getTypeName() {
	return type;
}

double reflections::TileType::hitBoxWidth() {
	return hitBoxW;
}

double reflections::TileType::hitBoxHeight() {
	return hitBoxH;
}

//Init all TileTypes.
bool reflections::TileType::init() {
	new TileType(GRASS, 1001, true, 64, 64);
	new TileType(LAVA, 1002, false, 64, 64);
	new TileType(WATER, 1003, false, 64, 64);
	new TileType(STONE, 1004, true, 64, 64);
	new TileType(STONE_LEDGE, 1005, true, 64, 14);
	new TileType(FAN, 1006, false, 64, 256, 64, 256);
	new TileType(FLAG, 1007, false, 100, 150, 10, 150);
	new TileType(DIRT, 1008, true, 64, 64);
	new TileType(GRASS_PATH, 1009, true, 64, 14);
	new TileType(ROCK, 1010, true, 320, 256, 300, 256);
	new TileType(HILL, 1011, true, 320, 256, 300, 256);
	new TileType(LAVA_VENT, 1012, false, 64, 64, 64, 250);
	new TileType(LANTERN, 1013, false, 173, 280);
	new TileType(THISTLE, 1014, false, 56, 128, 45, 120);
	return true;
}

void reflections::TileType::destroy() {
	for (auto & type : registry) {
		delete type.second;
	}
	registry.clear();
}

TileType * reflections::TileType::typeFromID(int id) {
	if (registry.count(id) > 0) {
		return registry[id];
	}
	return nullptr;
}

void reflections::TileType::updateTextureData() {
	for (const auto & entry : registry) {
		TileType * type = entry.second;
		if (type != nullptr) {
			type->getTextureData().update();
		}
	}
}