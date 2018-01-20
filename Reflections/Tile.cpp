#include "Tile.h"
#include "World.h"
#include "Entity.h"
#include "LivingEntity.h"
#include "GameManager.h"

using namespace reflections;

Tile::Tile(double x, double y, World & world, TileType & type) : location(x, y, world), hitBox(&location, type.hitBoxWidth(), type.hitBoxHeight()) {
	this->type = &type;
}

TileType & Tile::getType() {
	return *type;
}

void Tile::setType(TileType & type) {
	this->type = &type;
}

//Return a CLONE of the location that belongs to this tile.
//To edit location, use setLocation() method.
Location Tile::getLocation() {
	return location.clone();
}

HitBox & reflections::Tile::getHitBox() {
	return hitBox;
}

int reflections::Tile::getXOffset() {
	return location.getX() - type->getWidth() / 2;
}

int reflections::Tile::getYOffset() {
	return location.getY() + type->getHeight();
}

//Set this tiles location to another location.
void reflections::Tile::setLocation(Location & location) {
	World * oldWorld = &(this->location.getWorld());
	World * newWorld = &(location.getWorld());
	if (newWorld != oldWorld) {
		oldWorld->deleteTile(*this, false);
		newWorld->addTile(this);
	}
	this->location = location.clone();
}

//Remove a tile
void reflections::Tile::destroy() {
	location.getWorld().deleteTile(*this);
}

#include <iostream>
void reflections::Tile::onCollide(Entity * entity, BoxSide side) {

	GameManager & manager = GameManager::getInstance();

	switch (type->getTypeName()) {
	//Winning the level block
	case FLAG:
		if (entity->getType() == PLAYER) {
			World & world = getLocation().getWorld();

			//Kill all living entities in the world.
			for (Entity* & entity : *(world.getEntities())) {
				LivingEntity * le = nullptr;
				if (entity->getType() != PLAYER && (le = dynamic_cast<LivingEntity*>(entity)) != nullptr) {
					le->damage(le->getHealth());
				}
			}

			getLocation().getWorld().getTaskManager().scheduleTask([&]() {
				Level * level = manager.getLevelManager().getCurrentLevel();
				level->onEnd();
				LevelState state = level->getNextLevel() > 0 ? LevelState::NEXTLEVEL : LevelState::WIN;
				GameManager & manager = GameManager::getInstance();
				manager.getInputManager().setBlockInput(false);
				manager.getLevelManager().getCurrentLevel()->setLevelState(state);
				manager.setGameState(PAUSED);
			}, 4);
		}
		break;

	//Damaging
	case LAVA:
	case THISTLE:
		LivingEntity * le;
		if ((le = dynamic_cast<LivingEntity*>(entity)) != nullptr) {
			le->damage(1);
		}
		break;

	//Slowly moving up
	case FAN:
	case LAVA_VENT:
		entity->moveUp();
		break;
	}
}
