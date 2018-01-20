#pragma once
#include "Location.h"

namespace reflections {

	enum BoxSide {
		LEFT, RIGHT, UP, DOWN
	};

	//The hitbox class will allow two hitboxes to be compared to see if any collisions occur.
	class HitBox {
	private:
		Location * location;
		double leftX, rightX, topY, width, height, reach;
	public:
		HitBox(Location * location, double width, double height);

		void init(double width, double height);

		//Get the X and Y coordinates for a specific side of the hitbox.
		double getY(BoxSide side);
		double getX(BoxSide side);

		double getReach();
		
		double getWidth();
		double getHeight();

		//Check if this hitbox collides with another hitbox.
		//Returns NONE if falce, and side otherwise.
		bool collides(HitBox & hitBox2);
		
	};
}