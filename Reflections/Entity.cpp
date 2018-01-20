#include "Entity.h"
#include <cmath>
#include <algorithm>
#include "World.h"
#include "GameManager.h"

using namespace reflections;

//Constructor for entity.
//Every entity has at least a location and a type.
Entity::Entity(int x, int y, World & world, EntityType type, double maxSpeed, int width, int height, double hitBoxW, double hitBoxH) : location(x, y, world), hitBox(&location, hitBoxW, hitBoxH) {
	this->type = type;
	this->maxSpeed = maxSpeed;
	this->acceleration = 5;
	this->width = width;
	this->height = height;
	this->age = 0;
	this->remove = false;
}

//Constructor which defaults to image width and height as hitbox width and height.
Entity::Entity(int x, int y, World & world, EntityType type, double maxSpeed, int width, int height) : Entity(x, y, world, type, maxSpeed, width, height, width, height) {}

EntityType reflections::Entity::getType() {
	return type;
}

HitBox & reflections::Entity::getHitBox() {
	return hitBox;
}

void reflections::Entity::setMaxSpeed(double maxSpeed) {
	this->maxSpeed = maxSpeed;
}

double reflections::Entity::getMaxSpeed() {
	return maxSpeed;
}

void reflections::Entity::setAcceleration(double acceleration) {
	this->acceleration = acceleration;
}

double reflections::Entity::getAcceleration() {
	return acceleration;
}

void reflections::Entity::setRemove(bool remove) {
	this->remove = remove;
}

bool reflections::Entity::isRemove() {
	return remove;
}

//This calculates the new velocity of the entity.
void reflections::Entity::updateVelocity() {
	double newX, currentX;
	double newY, currentY;

	currentX = velocity.getX();
	currentY = velocity.getY();

	//Decrease velocity if signs are different.
	if (currentX != 0 && (velocityQueue.getX() == 0 || ((velocityQueue.getX() < 0) == (currentX > 0)))) {
		currentX = currentX < 0 ? std::min(currentX + acceleration, 0.0) : currentX = std::max(currentX - acceleration, 0.0);
	}
	
	//Calculate new velocity using input.
	newX = currentX + (acceleration * velocityQueue.getX());
	newY = currentY + (acceleration * velocityQueue.getY());

	//X
	if (abs(newX) <= maxSpeed) {									//If new value <= max value, set to newValue.
		velocity.setX(newX);
	}
	else if (abs(currentX) <= maxSpeed) {							//New value is above limit, old value is not. Means acceleration occured and
		velocity.setX(newX < 0 ? -maxSpeed : maxSpeed);				//has to be limited to max value.
	}
	else {															//Value was above limit and remains above limit.
		if (abs(newX) < abs(currentX)) {							//If value decreased after last input, it means the entity moved in opposite direction of
			velocity.setX(newX);									//its velocity. Should decrease twice as fast.
		}
		else {
			velocity.setX(currentX);								//Entity tried to accelerate beyond limit, which it was already above. Apply slowed down value.
		}
	}

	//Y
	if (abs(newY) <= maxSpeed) {									//If new value <= max value, set to newValue.
		velocity.setY(newY);
	}
	else if (abs(currentY) <= maxSpeed) {							//New value is above limit, old value is not. Means acceleration occured and
		velocity.setY(newY < 0 ? -maxSpeed : maxSpeed);				//has to be limited to max value.
	}
	else {															//Value was above limit and remains above limit.
		if (abs(newY) < abs(currentY)) {							//If value decreased after last input, it means the entity moved in opposite direction of
			velocity.setY(newY);									//its velocity. Should decrease twice as fast.
		}
		else {
			velocity.setY(currentY);								//Entity tried to accelerate beyond limit, which it was already above. Apply slowed down value.
		}
	}

	//Reset queue.
	velocityQueue.set(0, 0);
}

//Add values onto the current velocity. This ignores any limits set.
void reflections::Entity::addVelocity(double dx, double dy) {
	velocity.add(dx, dy);
}

//Methods to increase velocity based on current acceleration.

void reflections::Entity::setVelocity(double x, double y) {
	velocity.set(x, y);
}

Vector2d & reflections::Entity::getMovementDelta() {
	return deltaMovement;
}

void reflections::Entity::moveUp() {
	velocityQueue.setY(1);
}

void reflections::Entity::moveDown() {
	velocityQueue.setY(-1);
}

void reflections::Entity::moveLeft() {
	velocityQueue.setX(-1);
}

void reflections::Entity::moveRight() {
	velocityQueue.setX(1);
}

Vector2d & reflections::Entity::getVelocity() {
	return velocity;
}

Vector2d & reflections::Entity::getVelocityQueue() {
	return velocityQueue;
}

//Calculate where an entity would end up at current velocity.
Location reflections::Entity::nextLocation() {
	Location newLocation = location.clone();
	newLocation.add(velocity.getX(), velocity.getY());
	return newLocation;
}

//Get an interpolated estimate of the current whereabouts of the entity based on the current game tick.
Location reflections::Entity::virtualLocation() {

	GameTimer & timer = GameManager::getInstance().getGameTimer();
	Location clone = location.clone();
	double tickPct = 1 - timer.nextTickPct();

	//If tick is taking longer to proccess and the game cannot keep up, don't render the entity ahead of where it is.
	if (tickPct < 0) tickPct = 0;

	clone.addX(-(deltaMovement.getX() * tickPct));
	clone.addY(-(deltaMovement.getY() * tickPct));
	return clone;
}


//Return a CLONE of the location the entity is at.
//Use setLocation() to actually change an entities location.
Location Entity::getLocation() {
	return location.clone();
}

//Set an entities location.
void reflections::Entity::setLocation(Location & location) {
	//First check if the world has changed. If that's the case, switch the entity over to the other world.
	World * oldWorld = &(this->location.getWorld());
	World * newWorld = &(location.getWorld());

	this->location.set(location.getX(), location.getY()).setWorld(location.getWorld());

	if (newWorld != oldWorld) {
		//Delete from this worlds vector, but do not free memory.
		oldWorld->deleteEntity(*this, false);
		//Add this entity to the other world.
		newWorld->addEntity(this);
	}

	//Make sure X coordinate is not negative, because entities cannot go into negative X (Has to do with the way I render the world background)
	if (this->location.getX() < 0) {
		this->location.setX(0);
		velocity.setX(0);
	}

	//Stop negative Y as well.
	if (this->location.getY() < 0) {
		this->location.setY(0);
		velocity.setY(0);

		//If living entity, kill
		LivingEntity * le = nullptr;
		if ((le = dynamic_cast<LivingEntity*>(this)) != nullptr) {
			le->damage(1);
		}
	}
}

void reflections::Entity::setLocation(double x, double y) {
	setLocation(getLocation().set(x, y));
}

int reflections::Entity::getAge() {
	return age;
}

void reflections::Entity::ageTick() {
	age++;
}

void reflections::Entity::setWidth(int width) {
	this->width = width;
}

void reflections::Entity::setHeight(int height) {
	this->height = height;
}

int reflections::Entity::getWidth() {
	return width;
}

int reflections::Entity::getHeight() {
	return height;
}
