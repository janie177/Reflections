#pragma once
#include <vector>

//Chunk size in units (1.0 inside the location class is one unit, and this corresponds to one pixel at the base resolution defined in Renderer.cpp.
//If I render the game at this resolution, there wont be any variation in what you can see between different screen sizes. I can then simply scale the whole thing up/down
//and draw that on the screen. 
#define CHUNK_SIZE 500

namespace reflections {

	//Forward declaration
	class World;
	class Entity;
	class Tile;

	//Chunks are pieces of world in which tiles will be stored. They save a lot of processing power because I can see which chunk an entity/tile is in.
	//When updating and rendering the world, I will only have to look at chunks that are currently near the player, rather than having to check for every single tile.
	//Chunks are automatically created when I add a tile somewhere. Chunks that lack tiles are not created.
	class Chunk {
	private:
		World * world;
		int chunkID;
		std::vector<Tile*> * tiles;
	public:
		Chunk(int id, World * world);
		~Chunk();
		
		void addTile(Tile * tile);
		void deleteTile(Tile * tile, bool freeMem = true);
		std::vector<Tile*> * getTiles();
		bool destroy();
		int getChunkID();
		double getWorldX();
	};
}