#include "EntityManager.h"
#include "Player.h"
#include "Camera.h"
#include "Snail.h"
#include "TextEntity.h"
#include "World.h"
#include "Level.h"
#include "EvilPlant.h"
#include "PlantSpit.h"

using namespace reflections;

//Use a switch case to look for a matching EntityType. Then return a pointer to a newly created entity of the given type.
//If the type wasn't valid, a nullpointer will be returned.
Entity * reflections::EntityManager::createEntity(EntityType type, World & world) {
	switch (type) {
	case PLAYER:
		return new Player(*world.getLevel());
		break;
	case SNAIL:
		return new Snail(world);
		break;
	case CAMERA:
		return new Camera(*world.getLevel());
		break;
	case TEXT:
		return new TextEntity(world);
		break;
	case EVIL_PLANT:
		return new EvilPlant(world);
		break;
	case PLANT_SPIT:
		return new PlantSpit(world);
		break;
	default:
		return nullptr;
		break;
	}
}

Entity * reflections::EntityManager::createEntity(int type, World & world) {
	try {
		return createEntity((EntityType)type, world);
	}
	catch (...) {
		return nullptr;
	}
}
