#pragma once
#include "Entity.h"
#include "World.h"

namespace reflections {

	class EntityManager {
	public:
		//Method that creates a new instance of an entity based on the type provided.
		//Dynamically allocates memory so always keep the pointer it returns somewhere and free the memory in the end.
		static Entity * createEntity(EntityType type, World & world);

		//Same ad above method, but converts int to EntityType and returns null if that doesn't work.
		static Entity * createEntity(int type, World & world);
	};
}