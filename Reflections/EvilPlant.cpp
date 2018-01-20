#include "EvilPlant.h"
#include "GameManager.h"

reflections::EvilPlant::EvilPlant(World & world) : LivingEntity(0, 0, world, EVIL_PLANT, 0, 90, 105, 2050, 1, 1) {
	//Set initial value of faceLeft;
	faceLeft = true;

	lastAttack = 0;
}

void reflections::EvilPlant::onCollide(Entity & entity) {
}

void reflections::EvilPlant::onCollide(Tile & tile, BoxSide side) {
}

void reflections::EvilPlant::updateAnimation() {

}

double reflections::EvilPlant::gravityModifier() {
	return 1.0;
}

void reflections::EvilPlant::updateAI() {
	Location playerLocation = GameManager::getInstance().getLevelManager().getCurrentLevel()->getPlayer().getLocation();
	Location plantLocation = getLocation();
	double playerX = playerLocation.getX();
	double plantX = plantLocation.getX();

	//If the player is in range, interact.
	if (plantLocation.distance(playerLocation) < 450) {

		//Make the plant face the player.
		if (plantX < playerX) {
			if (faceLeft) {
				faceLeft = false;
				getTextureData().setFlipped(true);
			}
		}
		else {
			if (!faceLeft) {
				faceLeft = true;
				getTextureData().setFlipped(false);
			}
		}

		World & world = plantLocation.getWorld();
		long long int currentTick = world.getTick();
		//If projectile cooldown has expired, fire a new projectile.
		if (currentTick - lastAttack >= PLANT_ATTACK_INTERVAL) {
			lastAttack = currentTick;
			//Set attack animation, and halfway through the animation spawn the projectile
			getTextureData().setTexture(2051, 2050);

			//Fire the projectile.
			Entity * projectile = world.createEntity(PLANT_SPIT);
			Location playerLoc = GameManager::getInstance().getLevelManager().getCurrentLevel()->getPlayer().getLocation();
			projectile->setLocation(plantLocation.getX(), plantLocation.getY() + 90);
			Location projectileLocation = projectile->getLocation();

			//Calculate the vector between the player and the projectile
			double x = playerX -projectileLocation.getX();
			double y = ((playerLoc.getY() + 60) - projectileLocation.getY());
			y += abs(x / 6);
			//Set the velocity and then normalize and multiply it
			projectile->setVelocity(x, y);
			projectile->getVelocity().normalize().multiply(20 + (abs(x / 20)));
		}
	}
}

void reflections::EvilPlant::onDamage() {
}
