#include "Projectile.h"

reflections::Projectile::Projectile(int x, int y, World & world, EntityType type, double speed, int width, int height, int textureID, int maxAgeTicks, int damage) : TexturedEntity(x, y, world, type, speed, width, height, textureID) {
	this->damage = damage;
	this->maxAge = maxAgeTicks;
	setAcceleration(0);
}

void reflections::Projectile::update() {
	if (getAge() > maxAge) {
		onDestroy();
		setRemove(true);
	}
	else {
		onUpdate();
	}
}

void reflections::Projectile::setMaxAge(int maxAge) {
	this->maxAge = maxAge;
}

int reflections::Projectile::getMaxAge() {
	return maxAge;
}

int reflections::Projectile::getDamage() {
	return damage;
}

void reflections::Projectile::setDamage(int damage) {
	this->damage = damage;
}
