#pragma once
#include <cmath>

namespace reflections {

	//Forward declarations to prevent circular dependency
	class Location;

	//Simple vector class that allows me to give entities a velocity and add onto locations.
	class Vector2d {
	private:
		double x;
		double y;
		double length;
	public:
		Vector2d();
		Vector2d & normalize();
		Vector2d & add(double x, double y);
		Vector2d & add(Vector2d & vector2);
		Vector2d & set(double x, double y);
		Vector2d & setX(double x);
		Vector2d & setY(double y);
		Vector2d & calculate(Location & location1, Location & location2);
		Vector2d & multiply(double multiplier);

		Vector2d clone();
		double getX();
		double getY();

		double distance(Vector2d & vector2);
		double distance(double x, double y);
	};
}

