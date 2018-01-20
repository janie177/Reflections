#include "Vector2d.h"
#include <cmath>
#include "Location.h"

using namespace reflections;

reflections::Vector2d::Vector2d() {
	x = 0;
	y = 0;
}

//Make length of vector exactly 1.
Vector2d & reflections::Vector2d::normalize() {
	double length = sqrt(pow(x, 2) + pow(y, 2));
	if (length != 0) {
		x /= length;
		y /= length;
	}
	return *this;
}

Vector2d & reflections::Vector2d::add(double x, double y) {
	this->x += x;
	this->y += y;
	return *this;
}

Vector2d & reflections::Vector2d::add(Vector2d & vector2) {
	this->x += vector2.getX();
	this->y += vector2.getY();
	return *this;
}

Vector2d & reflections::Vector2d::set(double x, double y) {
	this->x = x;
	this->y = y;
	return *this;
}

Vector2d & reflections::Vector2d::setX(double x) {
	this->x = x;
	return *this;
}

Vector2d & reflections::Vector2d::setY(double y) {
	this->y = y;
	return *this;
}

//Calculate the vector between two points. Make sure to normalize afterward.
Vector2d & reflections::Vector2d::calculate(Location & location1, Location & location2) {
	this->x = location2.getX() - location1.getX();
	this->y = location2.getY() - location1.getX();
	return *this;
}

Vector2d & reflections::Vector2d::multiply(double multiplier) {
	x *= multiplier;
	y *= multiplier;
	return *this;
}

Vector2d reflections::Vector2d::clone() {
	return Vector2d().set(x, y);
}

double reflections::Vector2d::getX() {
	return x;
}

double reflections::Vector2d::getY() {
	return y;
}

double reflections::Vector2d::distance(Vector2d & vector2) {
	return distance(vector2.getX(), vector2.getY());
}

double reflections::Vector2d::distance(double x, double y) {
	double dx = this->x - x;
	double dy = this->y - y;
	return sqrt(pow(dx, 2) + pow(dy, 2));
}
