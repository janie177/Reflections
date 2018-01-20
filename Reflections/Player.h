#pragma once
#include "LivingEntity.h"

//Cooldown on switching world, prevents memory corruption when switching twice in the same tick.
#define PLAYER_TELEPORT_COOLDOWN 2

namespace reflections {

	//A player object, which contains all player data.
	class Player : public LivingEntity {
	private:
		Level * level;
		int lastTeleport;
	public:
		Player(Level & level);

		//Overridden methods from Interactable and LivingEntity
		void onCollide(Entity & entity);
		void updateAnimation();
		double gravityModifier();
		void updateAI();
		void onDeath();
		void onDamage();

		int getLastTeleport();
		void setLastTeleport(int lastTP);
	};
}