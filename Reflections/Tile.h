#pragma once

#include "TileType.h"
#include "Location.h"
#include "HitBox.h"

namespace reflections {

	//Forward declaration
	class World;
	class Entity;

	//Tiles make up the world.
	//Each tile has a pointer to the static type which holds all the data beloning to its type.
	//Each TileType also has their behaviour defined in a TileBehaviour class.
	//Constructor allows you to position the tile in the world, and set the type.
	class Tile {
	private:
		TileType * type;
		Location location;
		HitBox hitBox;
	public:
		Tile(double x, double y, World & world, TileType & type);
		TileType & getType();
		Location getLocation();

		//Get the hitbox
		HitBox & getHitBox();

		//Get the location in the world at which the entity texture should render and at which the hitbox should start.
		int getXOffset();
		int getYOffset();

		void onCollide(Entity * entity, BoxSide side);

		void setLocation(Location & location);
		void setType(TileType & type);
		void destroy();
	};
}

