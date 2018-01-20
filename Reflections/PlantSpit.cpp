#include "PlantSpit.h"
#include "LivingEntity.h"
#include "World.h"

reflections::PlantSpit::PlantSpit(World & world) : Projectile(0, 0, world, PLANT_SPIT, 15, 15, 10, 2052, 70, 1) {
}

double reflections::PlantSpit::gravityModifier() {
	return 0.4;
}

void reflections::PlantSpit::onCollide(Tile & tile, BoxSide side) {
	onDestroy();
}

void reflections::PlantSpit::onCollide(Entity & entity) {
	LivingEntity * le = nullptr;
	if (entity.getType() != EVIL_PLANT && (le = dynamic_cast<LivingEntity*>(&entity)) != nullptr) {
		le->damage(getDamage());
		onDestroy();
	}
}

void reflections::PlantSpit::onDestroy() {
	//Cool effect
	Location location = getLocation();
	location .getWorld().createParticleEffect(CLOUD, location.getX(), location.getY() + 5, 2, 1200, 0, 60, 60, 9999, 2.0, 0.5, 1.2, 15, 35, 3, 3)->addParticleType(4010, 100);

	//Remove
	setRemove(true);
}

void reflections::PlantSpit::onUpdate() {
	//Particle trail
	Location location = getLocation();
	location.getWorld().createParticleEffect(CLOUD, location.getX(), location.getY() + 5, 2, 1200, 60, 10, 10, 9999, 1.0, 0.5, 1.2, 15, 35, 3, 3)->addParticleType(4010, 100);
}

void reflections::PlantSpit::updateAnimation() {
}
