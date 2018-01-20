#include "Player.h"
#include "Level.h"
#include "Renderer.h"
#include "Tile.h"
#include <cmath>
#include <algorithm>
#include "GameManager.h"
#include "ParticleManager.h"
#include <iostream>

using namespace reflections;

reflections::Player::Player(Level & level) : LivingEntity(0, 0, level.getCurrentWorld(), PLAYER, 12, 56, 65, 2001, 3, 1) {
	this->level = &level;
	getHitBox().init(32, 62);
	setAcceleration(5);
	lastTeleport = 0;
}

void reflections::Player::onCollide(Entity & entity) {
}

void reflections::Player::updateAnimation() {
	if (getTextureData().getID() != 2004) {
		if (!canJump) {
			getTextureData().setTexture(2003);
			if (getVelocity().getX() < 0) {
				getTextureData().setFlipped(true);
			}
			else if (getVelocity().getX() > 0) {
				getTextureData().setFlipped(false);
			}
		}
		else if (getVelocity().getX() != 0) {
			getTextureData().setTexture(2002);
			getTextureData().setFlipped(getVelocity().getX() < 0);
		}
		else {
			getTextureData().setTexture(2001);
		}
	}
}

double reflections::Player::gravityModifier() {
	return 1.0;
}

void reflections::Player::updateAI() {
}

void reflections::Player::onDeath() {

	GameManager & manager = GameManager::getInstance();
	manager.getInputManager().setBlockInput(true);
	Location current = getLocation();
	getLocation().getWorld().createParticleEffect(CLOUD, current.getX(), current.getY() + 20, 2, 1200, 0, 60, 60, 9999, 2.0, 0.5, 1.2, 15, 35, 18, 18)->addParticleType(4007, 100);

	getLocation().getWorld().getTaskManager().scheduleTask([]() {
		GameManager & manager = GameManager::getInstance();
		manager.getInputManager().setBlockInput(false);
		manager.getLevelManager().getCurrentLevel()->setLevelState(LevelState::LOSE);
		manager.setGameState(PAUSED);
	}, DAMAGE_TICK_COOLDOWN - 1);
}

void reflections::Player::onDamage() {
	//If the player is teleporting right as they were hit, don't do anything.
	GameManager & manager = GameManager::getInstance();
	manager.getInputManager().setBlockInput(true);
	Location current = getLocation();
	getLocation().getWorld().createParticleEffect(CLOUD, current.getX(), current.getY() + 20, 2, 1200, 0, 60, 60, 9999, 2.0, 0.5, 1.2, 15, 35, 18, 18)->addParticleType(4007, 100);

	getLocation().getWorld().getTaskManager().scheduleTask([]() {
		GameManager & manager = GameManager::getInstance();
		manager.getInputManager().setBlockInput(false);
		Level * level = manager.getLevelManager().getCurrentLevel();
		level->getPlayer().setLocation(level->getPlayer().getLocation().set(level->getStartX(), level->getStartY()));
	}, DAMAGE_TICK_COOLDOWN - 1);
}

int reflections::Player::getLastTeleport() {
	return lastTeleport;
}

void reflections::Player::setLastTeleport(int lastTP) {
	lastTeleport = lastTP;
}