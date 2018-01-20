#include "Location.h"
#include <cmath>
#include "Util.h"

using namespace reflections;

double Location::getX() {
	return x;
}

double Location::getY() {
	return y;
}

//Calculate the distance between two locations using pythagoras
double Location::distance(Location & location) {
	//Commented out world check. This does't make sense to have because it only limits what you can do cross-dimension.
	//Instead it just returns the distance now, even if the worlds are not the same.
	//if (&(location.getWorld()) != world) return -1;

	double dx = x - location.getX();
	double dy = y - location.getY();
	return sqrt(pow(dx, 2) + pow(dy, 2));
}

Location & Location::add(double x, double y) {
	this->x += x;
	this->y += y;
	return *this;
}

Location & Location::set(double x, double y) {
	this->x = x;
	this->y = y;
	return *this;
}

Location & Location::add(Location & location2) {
	add(location2.getX(), location2.getY());
	return *this;
}

Location & Location::setX(double x) {
	this->x = x;
	return *this;
}

Location & Location::setY(double y) {
	this->y = y;
	return *this;
}

Location & Location::addX(double x) {
	setX(getX() + x);
	return *this;
}

Location & Location::addY(double y) {
	setY(getY() + y);
	return *this;
}

//Create a new location object with the same values as the main object.
Location Location::clone() {
	return Location(x, y, *world);
}

//Use the centralized method to calculate what chunk this location belongs to.
int reflections::Location::getChunk() {
	return chunkFromX(x);
}

World & reflections::Location::getWorld() {
	return *world;
}

Location & reflections::Location::setWorld(World & world) {
	//Set the world.
	this->world = &world;
	return *this;
}

//Overloading the + and - operators so you can add two locations onto eachother and substract them.
//This produces a new Location object which will be passed on by value. 
Location Location::operator+(Location & location2) {
	return Location(this->x + location2.getX(), this->y + location2.getY(), *world);
}

Location Location::operator-(Location & location2) {
	return Location(this->x - location2.getX(), this->y - location2.getY(), *world);
}

Location::Location(double x, double y, World & world) {
	this->world = &world;
	set(x, y);
}

Location::Location(World & world) {
	this->world = &world;
	set(0, 0);
}
