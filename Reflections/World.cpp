#include "World.h"
#include <iterator>
#include <algorithm>
#include "Interactable.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Tile.h"
#include "Chunk.h"
#include "Util.h"
#include "LivingEntity.h"
#include "Level.h"
#include "Text.h"
#include "TextEntity.h"
#include "HitBox.h"
#include "ParticleEffect.h"
#include "ParticleManager.h"
#include "Projectile.h"

#include <iostream>

using namespace reflections;

/*
	Note:
	When I started to work on this project, I had little experience with C++.
	One of the things I did not know were problematic, is the altering of collection while iterating over them.
	This led to a flawed design where vectors of entities were being edited during iteration.
	I did a quick edit, and now use a queue to list entities before removing them after the iteration has ended.
	I'm also aware now that pointers are a great way to reduce readability of a program and allow for memory leaks to exist.
	In the future I will use smart pointers instead, and only where necessary. Avoid pointers whenever possible.
*/

reflections::World::World(Level * level, std::string name, int iconID) : taskManager(this) {
	this->level = level;
	gravity = 4.0;
	maxGravity = MAX_GRAVITY_MULTIPLIER * -gravity;
	background = nullptr;
	chunks = new std::map<int, Chunk*>;
	entities = new std::vector<Entity*>;
	this->iconID = iconID;
	this->name = Text::create(name, 255, 255, 255);
	this->name->setHeight(this->name->getHeight() / 2);
	this->name->setWidth(this->name->getWidth() / 2);
	this->worldTick = 0;
}

reflections::World::~World() {
	destroy();
}

//Add an entity in this world.
bool reflections::World::addEntity(Entity * entity) {
	entitySpawnQueue.push_back(entity);
	return true;
}

//Add a tile to this world.
bool reflections::World::addTile(Tile * tile) {
	int tileChunk = tile->getLocation().getChunk();
	//Create chunk if it doesn't exist.
	if (!chunks->count(tileChunk)) {
		(*chunks)[tileChunk] = new Chunk(tileChunk, this);
	}

	//Finally add the tile to the chunk
	(*chunks)[tileChunk]->addTile(tile);
	return true;
}

//Create new entity and add it to the world.
//Returns pointer to new entity or nullptr.
Entity * reflections::World::createEntity(EntityType type) {
	Entity * entity = EntityManager::createEntity(type, *this);
	if (entity != nullptr) {
		addEntity(entity);
	}
	return entity;
}

//Create new tile in the world and return a reference to the tile.
Tile * reflections::World::createTile(int typeID, double x, double y) {
	TileType * type = TileType::typeFromID(typeID);
	if (type == nullptr) {
		std::cout << "Trying to create type for non-existing ID: " << typeID << "." << std::endl;
		return nullptr;
	}

	Tile * tile = new Tile(x, y, *this, *type);
	addTile(tile);
	return tile;
}

//Remove a tile from this world. Frees memory by default, unless specified otherwise.
bool reflections::World::deleteTile(Tile & tile, bool freeMem) {
	int chunk = tile.getLocation().getChunk();
	//Tile is not in this world, or there's no chunk for this tile
	if (&tile.getLocation().getWorld() != this || !chunks->count(chunk)) {
		return false;
	}

	//Delete the tile.
	(*chunks)[chunk]->deleteTile(&tile, freeMem);
	return true;
}

//Delete a chunk with the given ID.
void reflections::World::deleteChunk(int chunkID) {
	(*chunks)[chunkID]->destroy();
	chunks->erase(chunkID);
}

Chunk * reflections::World::getChunk(double worldX) {
	int chunkID = chunkFromX(worldX);
	if (chunks->count(chunkID) > 0) {
		return (*chunks)[chunkID];
	}
	return nullptr;
}

Chunk * reflections::World::getChunkAtIndex(int index) {
	if (chunks->count(index) > 0) {
		return (*chunks)[index];
	}
	return nullptr;
}

std::vector<Entity*>* reflections::World::getEntities() {
	return entities;
}

//Remove an entity from the world.
bool reflections::World::deleteEntity(Entity & entity, bool freeMem) {
	if (freeMem) {
		entity.setRemove(true);
	}
	else {
		entityRemoveQueue.push_back(&entity);
	}
	return true;
}

//Set the background for this world.
bool reflections::World::setBackground(int texture1, int texture2, int texture3, int texture4) {
	if (this->background != nullptr) {
		delete this->background;
	}
	this->background = new Background(this, texture1, texture2, texture3, texture4);
	return true;
}

Background & reflections::World::getBackground() {
	return *background;
}

void reflections::World::setGravity(double gravity) {
	this->gravity = gravity;
}

double reflections::World::getGravity() {
	return gravity;
}

//Spawn all queued entities and remove all entities queued for removal.
//This has to be done using a queue because otherwise iterators become invalid when altering the entities vector during a tick.
//This is called after the world tick happens, and when the player switches worlds.
void reflections::World::applyEntityQueues() {

	for (Entity* & entity : entitySpawnQueue) {

		if (entity->getType() == PLAYER) {
			entities->push_back(entity);
		}
		else {
			entities->insert(entities->begin(), entity);
		}

		//After adding the entity, resolve any collisions with their current location if they are interactable.
		//Find the nearest free spot and place them there.
		Interactable * interactable = dynamic_cast<Interactable*>(entity);

		if (interactable == nullptr) {
			continue;
		}

		Chunk * chunks[3];
		Location startLocation = entity->getLocation();
		Location newLocation = startLocation;
		int chunkID = chunkFromX(startLocation.getX());
		bool down = true;
		chunks[0] = getChunkAtIndex(chunkID);
		chunks[1] = getChunkAtIndex(chunkID + 1);
		chunks[2] = getChunkAtIndex(chunkID - 1);

		for (int i = 0; i < 3; i++) {
			Chunk * chunk = chunks[i];
			if (chunk != nullptr) {
				auto itr = chunk->getTiles()->begin();
				while (itr != chunk->getTiles()->end()) {
					if (*itr != nullptr && (*itr)->getType().isSolid() && (*itr)->getHitBox().collides(entity->getHitBox())) {
						double moved;
						if (down) {
							moved = ((*itr)->getHitBox().getY(DOWN) - entity->getHitBox().getY(UP));
						}
						else {
							moved = ((*itr)->getHitBox().getY(UP) - entity->getHitBox().getY(DOWN));
						}
						newLocation = entity->getLocation();
						newLocation.addY(moved);
						if (down && newLocation.getY() < entity->getHitBox().getHeight()) {
							down = false;
							entity->setLocation(startLocation);
						}
						else {
							entity->setLocation(newLocation);
						}
						//Reset the loop and check again.
						i = 0;
						break;
					}
					itr++;
				}
			}
		}
	}

	//Remove entities that are marked for removal
	for (Entity* & entity : entityRemoveQueue) {
		std::vector<Entity*>::iterator itr = entities->begin();

		while (itr != entities->end()) {
			if (*itr == entity) {
				itr = entities->erase(itr);
				break;
			}
			itr++;
		}
	}

	//Clear remove queue
	entityRemoveQueue.clear();

	//After adding all queued entity spawns, clear the queue.
	entitySpawnQueue.clear();
}

void reflections::World::addParticleEffect(ParticleEffect * effect) {
	effects.push_back(effect);
}

ParticleEffect * reflections::World::createParticleEffect(EffectType type, double x, double y, int layer, double activationRange, double particleRange, int pCount, int totalParticles, double pps, double lifeSpan, double pAgeMin, double pAgeMax, double pSpeedMin, double pSpeedMax, double spawnXOffset, double spawnYOffset) {
	ParticleEffect * effect = ParticleManager::create(type, x, y, layer, activationRange, particleRange, pCount, totalParticles, pps, lifeSpan, pAgeMin, pAgeMax, pSpeedMin, pSpeedMax, spawnXOffset, spawnYOffset);
	addParticleEffect(effect);
	return effect;
}

void reflections::World::removeParticleEffect(ParticleEffect * effect) {
	int index = 0;
	for (ParticleEffect* & eff : effects) {
		if (eff == effect) {
			effects.erase(effects.begin() + index);
			delete eff;
			return;
		}
		index++;
	}
}

void reflections::World::renderParticles(int layer, SDL_Renderer * renderer, double deltaSeconds, double camX, double camY) {
	for (ParticleEffect* & eff : effects) {
		if (eff->getLayer() == layer) {
			eff->render(renderer, deltaSeconds, camX, camY);
		}
	}
}

Text * reflections::World::getName() {
	return name;
}

int reflections::World::getIconID() {
	return iconID;
}

long long int reflections::World::getTick() {
	return worldTick;
}

TaskManager & reflections::World::getTaskManager() {
	return taskManager;
}

//Destroy all dynamically allocated objects so that they wont cause a memory leak.
bool reflections::World::destroy() {
	int i;

	applyEntityQueues();

	try {
		//Loop through chunks, have them delete their tiles, then free all the memory.
		std::map<int, Chunk*>::iterator it;
		it = chunks->begin();
		while (it != chunks->end()) {
			(it->second)->destroy();
			it++;
		}
		chunks->clear();
		delete chunks;

		//Loop through entities and delete them.
		std::vector<Entity*>::iterator itr = entities->begin();
		while (itr != entities->end()) {
			delete *itr;
			itr++;
		}
		entities->clear();
		delete entities;

		for (i = 0; i < effects.size(); i++) {
			ParticleEffect * effect = effects[i];
			delete effect;
		}
		effects.clear();

		//Delete the background. Only contains ints.
		delete background;

		//Delete text generated for name.
		name->destroy();
	}

	catch (...) {
		return false;
	}

return true;
}

//Update every entity in the world, update locations based on direction, speed and modifiers.
//Also detect collisions.
void reflections::World::updateTick() {
	worldTick++;
	int index;
	Interactable * interact = nullptr;
	LivingEntity * living = nullptr;
	Textured * textured = nullptr;
	Projectile * projectile = nullptr;
	BoxSide hitBoxSide;
	double moved = 0;
	Chunk * chunks[3];
	std::map<Tile*, BoxSide> collisions;
	std::vector<Tile*> nearby;

	//Execute any delayed tasks for this tick
	taskManager.execute();

	//Loop over effects and update them.
	std::vector<ParticleEffect*>::iterator itr = effects.begin();
	while (itr != effects.end()) {
		if (!(*itr)->update()) {
			delete *itr;
			itr = effects.erase(itr);
		}
		else {
			itr++;
		}
	}

	//Loop over entities and update them. Collisions and stuff.
	for (std::vector<Entity*>::iterator it = (*entities).begin(); it != (*entities).end(); it++) {

		Entity * entity = (*it);

		//If entity is null somehow, don't try to update it.
		if (entity == nullptr) {
			it = entities->erase(it);
			continue;
		}

		//Update the entity's age (Add 1 to it).
		entity->ageTick();

		//Remove entities that are marked for removal.
		if (entity->isRemove()) {
			it = entities->erase(it);
			delete entity;
			continue;
		}

		//Check if entity is textured. If so, update texture
		if ((textured = dynamic_cast<Textured*>(entity)) != nullptr) {
			textured->getTextureData().update();
		}

		//If entity is a living entity, update their AI.
		if ((living = dynamic_cast<LivingEntity*>(entity)) != nullptr) {
			living->updateAI();
		}

		//If the entity is a projectile, update it.
		if ((projectile = dynamic_cast<Projectile*>(entity)) != nullptr) {
			projectile->update();
		}

		//If true, entity is interactable. Apply gravity to the entity.
		if ((interact = dynamic_cast<Interactable*>(entity)) != nullptr && entity->getVelocity().getY() > maxGravity) {
			double actualGravity = interact->gravityModifier() * gravity;
			entity->addVelocity(0, -actualGravity);
		}

		//Update entity velocity. This slows the entity down if no movement is queued, and accelerates the entity otherwise.
		entity->updateVelocity();

		//Get the location the entity would move to this tick if there's no obstruction. X axis is moved first and then Y. This prevents diagonal movement which is hard to
		//prevent from collidion with AABB. It makes sense because it's axis aligned after all.
		Location current = entity->getLocation();
		Location to = entity->nextLocation();

		//If entity is interactable, look for possible collisions with tiles and entities.
		if (interact != nullptr) {

			//Store original position.
			double startX = current.getX();
			double dx = to.getX() - startX;
			double dy = to.getY() - current.getY();

			//Get the two bordering chunks. If a chunk contains a really large overlapping object, it'll still be able to detect collision.
			//A more optimized way to do it is to calculate which chunk is closest to the player taking dx into account.
			//This would loop through less chunks and thus save processing power, though it would also possibly cause problems when entities move fast or
			//are on the border of a chunk or when the chunk contains a really large object. This is the "safest" way to do it at a small cost.
			int chunkID = chunkFromX(startX);
			chunks[0] = getChunkAtIndex(chunkID);
			chunks[1] = getChunkAtIndex(chunkID + 1);
			chunks[2] = getChunkAtIndex(chunkID - 1);

			//Find all nearby possible collisions in a broad check.
			double distance;
			double furthestDistance;
			double added = sqrt(pow(dx, 2) + pow(dy, 2));
			for (Chunk* & chunk : chunks) {
				if (chunk == nullptr) {
					continue;
				}
				for (Tile* & tile : *chunk->getTiles()) {
					if (tile == nullptr) {
						continue;
					}
					//Get the distance between the origin of the tile and the location. This does not yet take movement into account.
					distance = current.distance(tile->getLocation());
					//This variable represents the utmost longest distance that the two entities can be from eachother while still colliding.
					//Takes the dx and dy movement in an optimal scenario into account.
					furthestDistance = tile->getHitBox().getReach() + entity->getHitBox().getReach() + added;
					if (distance <= furthestDistance) {
						nearby.push_back(tile);
					}
				}
			}

			//Check for collision detection by comparing tile hitboxes to player hitboxes.
			//Set X location
			entity->setLocation(entity->getLocation().add(dx, 0));
			for (Tile* & tile : nearby) {
				if (entity->getHitBox().collides(tile->getHitBox())) {
					if (dx >= 0) {
						hitBoxSide = LEFT;
						moved = tile->getHitBox().getX(LEFT) - entity->getHitBox().getX(RIGHT);
					}
					else {
						hitBoxSide = RIGHT;
						moved = tile->getHitBox().getX(RIGHT) - entity->getHitBox().getX(LEFT);
					}

					if (tile->getType().isSolid()) {
						entity->setLocation(entity->getLocation().addX(moved));
						entity->getVelocity().setX(0);
						interact->onCollide(*tile, hitBoxSide);
						tile->onCollide(entity, hitBoxSide);
						break;
					}
					collisions[tile] = hitBoxSide;
				}
			}
			


			//Set Y location after setting X location.
			entity->setLocation(entity->getLocation().add(0, dy));
			for (Tile* & tile : nearby) {
				if (entity->getHitBox().collides(tile->getHitBox())) {
					if (dy >= 0) {
						hitBoxSide = DOWN;
						moved = tile->getHitBox().getY(DOWN) - entity->getHitBox().getHeight();
					}
					else {
						hitBoxSide = UP;
						moved = tile->getHitBox().getY(UP);
					}

					if (tile->getType().isSolid()) {
						entity->setLocation(entity->getLocation().setY(moved));
						entity->getVelocity().setY(0);
						interact->onCollide(*tile, hitBoxSide);
						tile->onCollide(entity, hitBoxSide);
						break;
					}
					collisions[tile] = hitBoxSide;
				}
			}
			

			//See if the blocks that had collision are still colliding with the player.
			//If they are, call the onCollide method.
			for (std::map<Tile*, BoxSide>::iterator it = collisions.begin(); it != collisions.end(); ++it) {
				if (entity->getHitBox().collides(it->first->getHitBox())) {
					interact->onCollide(*(it->first), it->second);
					it->first->onCollide(entity, it->second);
				}
			}

			//Clear collision map again.
			collisions.clear();
			nearby.clear();

			//Set the entities movement delta.
			Location now = entity->getLocation();
			entity->getMovementDelta().set(now.getX() - current.getX(), now.getY() - current.getY());

			//Loop through all entities to see if there's a collision.
			for (Entity* & entity2 : *entities) {
				if (entity2 != nullptr && entity->getHitBox().collides(entity2->getHitBox())) {
					//Entity collision detected. Call onCollide
					interact->onCollide(*entity2);
				}
			}
		}
		//Entity is not interactable. Just set their location.
		else {
			entity->setLocation(to);
		}
		//After applying AI stuff and updating otherwise, update the animation for textured entities.
		if (textured != nullptr) {
			((TexturedEntity*)entity)->updateAnimation();
		}
	}

	//Spawn and remove entities after all other game logic is done.
	applyEntityQueues();
}

Level * reflections::World::getLevel() {
	return level;
}
