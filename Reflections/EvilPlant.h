#pragma once
#include "LivingEntity.h"

#define PLANT_ATTACK_INTERVAL 60

namespace reflections {


	//A player object, which contains all player data.
	class EvilPlant : public LivingEntity{
	private:
		bool faceLeft;
		long long int lastAttack;
	public:
		EvilPlant(World & world);

		//Overridden methods from Interactable and LivingEntity
		void onCollide(Entity & entity);
		void onCollide(Tile & tile, BoxSide side);
		void updateAnimation();
		double gravityModifier();
		void updateAI();
		void onDamage();
	};
}