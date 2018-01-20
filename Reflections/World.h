#pragma once
#include <map>
#include <vector>
#include "TileType.h"
#include "Background.h"
#include "TaskManager.h"
#include "Text.h"
#include "ParticleManager.h"

#define MAX_GRAVITY_MULTIPLIER 9

namespace reflections {

	//Forward declaration
	class Level;
	class Chunk;
	class Tile;
	class Entity;
	class ParticleEffect;
	enum EntityType;

	//A world contains Chunks, entities and a background.
	//Those are all stored as pointers to dynamically allocated memory.
	class World {
	private:
		Background * background;
		std::map<int, Chunk*> * chunks;
		std::vector<Entity*> * entities;
		std::vector<Entity*> entitySpawnQueue;
		std::vector<Entity*> entityRemoveQueue;
		std::vector<ParticleEffect*> effects;
		TaskManager taskManager;
		double gravity;
		double maxGravity;
		Level * level;
		Text * name;
		int iconID;
		long long int worldTick;
	public:
		World(Level * level, std::string name, int iconID);
		~World();

		//Add existing entities and tiles to the world. They have to point to dynamically allocated memory.
		bool addEntity(Entity * entity);
		bool addTile(Tile * tile);

		//Create an entity and allocate memory. Returns a pointer to the entity, or nullptr if it couldn't be created.
		Entity * createEntity(EntityType type);

		//Create a tile and allocate memory for it.
		Tile * createTile(int typeID, double x, double y);

		//Delete entities, chunks and tiles. Optionally free memory allocated. Defaults to freeing memory.
		bool deleteTile(Tile & tile, bool freeMem = true);
		bool deleteEntity(Entity & entity, bool freeMem = true);
		void deleteChunk(int chunkID);

		Chunk * getChunk(double worldX);
		Chunk * getChunkAtIndex(int index);

		std::vector<Entity*> * getEntities();

		bool setBackground(int texture1, int texture2, int texture3, int texture4);
		Background & getBackground();

		//Modify worlds gravity.
		void setGravity(double gravity);
		double getGravity();

		//Update the entity queues for removing and spawning
		void applyEntityQueues();

		//Adding and removing particle effects.
		void addParticleEffect(ParticleEffect * effect);
		ParticleEffect * createParticleEffect(EffectType type, double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset);
		void removeParticleEffect(ParticleEffect * effect);

		void renderParticles(int layer, SDL_Renderer * renderer, double deltaSeconds, double camX, double camY);

		Text * getName();
		int getIconID();

		//Tick of the world. Since worlds don't always get updated (If the player is in another one depending on the level) this doesn't always equal game tick.
		//This is used for delaying world specific tasks.
		long long int getTick();

		//Get the task manager to schedule tasks
		TaskManager & getTaskManager();

		//The end of the world as we know it.
		bool destroy();

		//Update the world and everything in it.
		void updateTick();

		//Get the level this world belongs to.
		Level * getLevel();
	};
}

