#include "Particle.h"
#include <cmath>

using namespace reflections;

reflections::Particle::Particle() {
	alive = false;
	age = 0;
	speed = 0;
	maxAge = 0;
}

void reflections::Particle::kill() {
	alive = false;
}

void reflections::Particle::spawn(double age, double speed, int textureID) {
	this->speed = speed;
	this->maxAge = age;
	this->age = 0;
	this->location.set(0, 0);
	this->direction.set(0, 0);
	this->textureData.setTexture(textureID);
	this->alive = true;
}

double reflections::Particle::getMaxAge() {
	return maxAge;
}

double reflections::Particle::getAge() {
	return age;
}

bool reflections::Particle::isAlive() {
	return alive;
}

double reflections::Particle::getSpeed() {
	return speed;
}

Vector2d & reflections::Particle::getDirection() {
	return direction;
}

TextureData & reflections::Particle::getTextureData() {
	return textureData;
}

double reflections::Particle::getX() {
	return location.getX();
}

double reflections::Particle::getY() {
	return location.getY();
}

void reflections::Particle::setX(double x) {
	location.setX(x);
}

void reflections::Particle::setY(double y) {
	location.setY(y);
}

//Get how far the particle is removed from the origin.
double reflections::Particle::getDistance() {
	return location.distance(0, 0);
}

int reflections::Particle::getTextureID() {
	return textureData.getID();
}

void reflections::Particle::setTextureID(int id) {
	textureData.setTexture(id);
}

void reflections::Particle::setSpeed(double speed) {
	this->speed = speed;
}

void reflections::Particle::setDirection(double x, double y) {
	direction.set(x,y).normalize();
}

void reflections::Particle::update(double seconds) {
	if (alive) {
		location.add(direction.getX() * speed * seconds, direction.getY() * speed * seconds);
		age += seconds;
	}
}
