#pragma once
#include "Location.h"
#include "Vector2d.h"
#include "HitBox.h"

namespace reflections {

	//Forward declarations to prevent circular dependency
	class Level;
	class World;
	class Tile;

	//Enum with the different types of entities.
	//Useful when abstraction is in place, and the type of an entity class needs to be found.
	enum EntityType {
		PLAYER,		//0
		CAMERA,		//1
		TEXT,		//2
		SNAIL,		//3
		EVIL_PLANT,	//4
		PLANT_SPIT	//5
	};

	class Entity {
	private:
		Location location;
		Vector2d velocity;
		Vector2d velocityQueue;
		Vector2d deltaMovement;
		HitBox hitBox;
		double maxSpeed;
		double acceleration;
		EntityType type;
		int width, height;
		bool remove;
		int age;

	protected:
		Vector2d & getVelocityQueue();

	public:
		Entity(int x, int y, World & world, EntityType type, double maxSpeed, int width, int height);
		Entity(int x, int y, World & world, EntityType type, double maxSpeed, int width, int height, double hitBoxW, double hitBoxH);

		//Get the entity type
		EntityType getType();

		//Get the hitbox
		HitBox & getHitBox();

		//Methods to alter an entities movement.
		void setMaxSpeed(double maxSpeed);
		double getMaxSpeed();

		//Set/get acceleration.
		void setAcceleration(double acceleration);
		double getAcceleration();

		void setRemove(bool remove);
		bool isRemove();

		//If an int is +1, add acceleration onto velocity.
		//If -1, remove acceleration from velocity.
		//This will go up to a maximum limit.
		//Use INCREASE DECREASE and NEUTRAL
		void updateVelocity();
		//Add raw values onto the velocity. This ignores limits.
		void addVelocity(double dx, double dy);
		void setVelocity(double x, double y);

		Vector2d & getMovementDelta();

		virtual void moveUp();
		virtual void moveDown();
		virtual void moveLeft();
		virtual void moveRight();

		Vector2d & getVelocity();

		//Calculate the location where the entity will end up with current velocity.
		Location nextLocation();

		//Get an estimate of where the entity would be based on interpolated values. Or extrapolated I guess because it's based on an estimated end value?
		Location virtualLocation();

		//Location methods.
		Location getLocation();
		void setLocation(Location & location);
		void setLocation(double x, double y);

		//Age
		int getAge();
		void ageTick();

		//Hitbox related data (Calculate offset once upon setting, then use forever.
		void setWidth(int width);
		void setHeight(int height);
		int getWidth();
		int getHeight();

		//Destructor
		virtual ~Entity() = 0 {};
	};
}