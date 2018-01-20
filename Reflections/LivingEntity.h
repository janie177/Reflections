#pragma once
#include "TexturedEntity.h"
#include "Interactable.h"

#define DAMAGE_TICK_COOLDOWN 15

namespace reflections {

	//Livingentity is an entitiy that has a texture, is interactable and allows AI/health/damage
	class LivingEntity : public TexturedEntity, public Interactable {
	private:
		int health;
		int maxHealth;
		int attackDamage;
		long long int lastDamageTick;
	protected:
		bool canJump;
	public:
		//Constructor
		LivingEntity(int x, int y, World & world, EntityType type, double speed, int width, int height, int textureID, int health, int damage);

		//Pure virtual methods that will allow for different behaviour for each entity type.
		virtual void updateAI() = 0;
		virtual void onDamage() = 0;
		virtual void onDeath();

		//Override from Entity
		void moveUp();

		virtual void onCollide(Tile & tile, BoxSide side);

		void jump();

		//Damage the entity
		bool damage(int amount);

		//Getters and setters for health/damage.
		int getHealth();
		int getMaxHealth();
		void setMaxHealth(int maxHealth);
		void setHealth(int health);
		int getAttackDamage();
		void setAttackDamage(int damage);
	};
}