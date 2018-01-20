#include "HitBox.h"
#include <cmath>

using namespace reflections;

reflections::HitBox::HitBox(Location * location, double width, double height) {
	this->location = location;
	init(width, height);
}

void reflections::HitBox::init(double width, double height) {
	this->leftX = width / 2;
	this->rightX = width - leftX;
	this->topY = height;
	this->width = width;
	this->height = height;
	this->reach = sqrt(pow(rightX, 2) + pow(height, 2));
}

double reflections::HitBox::getY(BoxSide side) {
	if (side == UP) {
		return location->getY() + topY;
	}
	return location->getY();
}

double reflections::HitBox::getX(BoxSide side) {
	if (side == RIGHT) {
		return location->getX() + rightX;
	}
	return location->getX() - leftX;
}

double reflections::HitBox::getReach() {
	return reach;
}

double reflections::HitBox::getWidth() {
	return width;
}

double reflections::HitBox::getHeight() {
	return height;
}

//AABB collision detection.
bool reflections::HitBox::collides(HitBox & hitBox2) {
	return getX(LEFT) < hitBox2.getX(RIGHT) && getX(RIGHT) > hitBox2.getX(LEFT) && getY(UP) > hitBox2.getY(DOWN) && getY(DOWN) < hitBox2.getY(UP);
}
