#include "Chunk.h"
#include "Util.h"
#include <algorithm>
#include "World.h"
#include "Tile.h"

using namespace reflections;

reflections::Chunk::Chunk(int id, World * world) {
	this->chunkID = id;
	this->world = world;
	//Allocate memory for tiles
	this->tiles = new std::vector<Tile*>;
}

reflections::Chunk::~Chunk() {
	destroy();
}

void reflections::Chunk::addTile(Tile * tile) {
	tiles->push_back(tile);
}

//Remove a tile from the vector of tiles.
void reflections::Chunk::deleteTile(Tile * tile, bool freeMem) {
	tiles->erase(std::remove(tiles->begin(), tiles->end(), tile), tiles->end());

	//If freeMem is set to true, free the memory location of Tile.
	if (freeMem) {
		delete tile;
	}

	//If there's no longer any tiles present, delete this chunk.
	if (tiles->empty()) {
		world->deleteChunk(chunkID);
	}
}

std::vector<Tile*> * reflections::Chunk::getTiles() {
	return tiles;
}

//Loop through tiles and delete them
bool reflections::Chunk::destroy() {
	for (auto const & tile : *tiles) {
		delete tile;
	}
	delete tiles;
	return true;
}

int reflections::Chunk::getChunkID() {
	return chunkID;
}

double reflections::Chunk::getWorldX() {
	return worldXFromChunk(chunkID);
}
