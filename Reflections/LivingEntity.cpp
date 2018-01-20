#include "LivingEntity.h"
#include "Tile.h"
#include "GameManager.h"


reflections::LivingEntity::LivingEntity(int x, int y, World & world, EntityType type, double speed, int width, int height, int textureID, int health, int damage) 
	: TexturedEntity(x, y, world, type, speed, width, height, textureID) {
	this->health = health;
	this->attackDamage = damage;
	this->canJump = false;
	lastDamageTick = 0;
}

void reflections::LivingEntity::onDeath() {
	World & world = getLocation().getWorld();
	Location current = getLocation();
	world.createParticleEffect(CLOUD, current.getX(), current.getY() + 20, 2, 1200, 0, 60, 60, 9999, 2.0, 0.5, 1.2, 15, 35, 18, 18)->addParticleType(4007, 100);
	setRemove(true);
}

void reflections::LivingEntity::moveUp() {
	getVelocityQueue().setY(1);
	canJump = false;
}

void reflections::LivingEntity::onCollide(Tile & tile, BoxSide side) {
	if (tile.getType().isSolid() && side == UP) {
		canJump = true;
	}
}

void reflections::LivingEntity::jump() {
	if (canJump && getVelocity().getY() == 0 && getVelocityQueue().getY() == 0) {
		addVelocity(0, 30);
		canJump = false;
	}
}

bool reflections::LivingEntity::damage(int amount) {
	long long int currentTick = GameManager::getInstance().getGameTimer().getTick();
	if (currentTick - lastDamageTick >= DAMAGE_TICK_COOLDOWN) {
		setHealth(health - amount);
		lastDamageTick = currentTick;
		return true;
	}
	return false;
}

int reflections::LivingEntity::getHealth() {
	return health;
}

int reflections::LivingEntity::getMaxHealth() {
	return maxHealth;
}

void reflections::LivingEntity::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}

void reflections::LivingEntity::setHealth(int health) {
	this->health = health;
	if (health > 0) {
		onDamage();
	}
	else {
		onDeath();
	}
}

int reflections::LivingEntity::getAttackDamage() {
	return attackDamage;
}

void reflections::LivingEntity::setAttackDamage(int damage) {
	this->attackDamage = damage;
}
