#pragma once
#include "LivingEntity.h"

namespace reflections {

	class Snail : public LivingEntity {
	private:
		bool hide;
		bool right;
	public:
		Snail(World & world);

		void onCollide(Entity & entity);
		void onCollide(Tile & tile, BoxSide side);
		void updateAnimation();
		double gravityModifier();
		void updateAI();
		void onDamage();
	};

}