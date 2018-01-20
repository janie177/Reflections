#pragma once
#include "Vector2d.h"
#include "TextureData.h"

namespace reflections {

	class Particle {
	private:
		double age;
		double maxAge;
		double speed;
		Vector2d location;
		Vector2d direction;
		bool alive;
		TextureData textureData;
	public:
		Particle();

		void kill();
		void spawn(double age, double speed, int textureID);

		double getMaxAge();
		double getAge();
		bool isAlive();
		double getSpeed();
		Vector2d & getDirection();

		TextureData & getTextureData();

		double getX();
		double getY();
		void setX(double x);
		void setY(double y);

		double getDistance();

		int getTextureID();
		void setTextureID(int id);
		void setSpeed(double speed);
		void setDirection(double x, double y);

		void update(double seconds);
	};
}