#pragma once
#include "Projectile.h"

namespace reflections {

	class PlantSpit : public Projectile {
	private:
	public:
		PlantSpit(World & world);
		virtual double gravityModifier();
		virtual void onCollide(Tile & tile, BoxSide side);
		virtual void onCollide(Entity & entity);
		virtual void onDestroy();
		virtual void onUpdate();
		void updateAnimation();
	};
}