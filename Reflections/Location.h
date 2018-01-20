#pragma once

namespace reflections {

	//Forward declarations to prevent circular dependency
	class World;

	class Location {
	private:
		double x;
		double y;
		World * world;
	public:
		//Getters, setters and other useful things.
		double getX();
		double getY();
		double distance(Location & location);
		Location & add(double x, double y);
		Location & add(Location & location2);
		Location & set(double x, double y);
		Location & setX(double x);
		Location & setY(double y);
		Location & addX(double x);
		Location & addY(double y);
		Location clone();

		//Get chunk by ID.
		int getChunk();

		//Get world
		World & getWorld();
		Location & setWorld(World & world);

		//Overloading because why not
		Location operator + (Location & location2);
		Location operator - (Location & location2);

		//Constructors.
		Location(double x, double y, World & world);
		Location(World & world);
	};
}

