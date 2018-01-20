#include "Snail.h"
#include "GameManager.h"
#include "Random.h"
#include "Tile.h"

reflections::Snail::Snail(World & world) : LivingEntity(0, 0, world, SNAIL, 3, 80, 60, 2010, 1, 1) {
	hide = false;
	right = true;
}

void reflections::Snail::onCollide(Entity & entity) {

}

void reflections::Snail::onCollide(Tile & tile, BoxSide side) {
	if (tile.getType().isSolid() && side == LEFT || side == RIGHT) {
		canJump = true;
		right = !right;
	}
}


void reflections::Snail::updateAnimation() {
	double x = getVelocity().getX();
	if (x > 0) {
		getTextureData().setFlipped(true);
	}
	else if (x < 0) {
		getTextureData().setFlipped(false);
	}
}

double reflections::Snail::gravityModifier() {
	return 1.0;
}

void reflections::Snail::updateAI() {
	double playerDistance = GameManager::getInstance().getLevelManager().getCurrentLevel()->getPlayer().getLocation().distance(getLocation());
	if (playerDistance < 150) {
		if (!hide) {
			hide = true;
			getTextureData().setTexture(2011, 2013);
		}
	}
	else if (hide) {
		hide = false;
		getTextureData().setTexture(2012, 2010);
	}

	//Movement
	if (!hide) {
		if (Random::getInstance().randomInt(0, 100) == 0) {
			right = !right;
		}

		if (right) {
			moveRight();
		}
		else {
			moveLeft();
		}
	}
}

void reflections::Snail::onDamage() {
}
