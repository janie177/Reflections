#pragma once
#include "TexturedEntity.h"
#include "Interactable.h"

namespace reflections {

	class Projectile : public TexturedEntity, public Interactable {
	private:
		int damage;
		int maxAge;
	public:
		//Constructor
		Projectile(int x, int y, World & world, EntityType type, double speed, int width, int height, int textureID, int maxAgeTicks, int damage);

		//Override from Interactable.
		virtual void onCollide(Tile & tile, BoxSide side) = 0;
		virtual void onCollide(Entity & entity) = 0;
		//On projectile death (So when age is exceeded or when hitting something).
		virtual void onDestroy() = 0;
		//Called every tick
		virtual void onUpdate() = 0;

		//Called every tick
		void update();

		//Setting/Getting the damage and age stuff
		void setMaxAge(int maxAge);
		int getMaxAge();

		int getDamage();
		void setDamage(int damage);
	};
}