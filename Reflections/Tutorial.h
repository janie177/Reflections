#pragma once
#include "Level.h"

/*
	This is the first level: tutorial.	
*/

namespace reflections {

	class Tutorial : public Level {
	private:
	public:
		std::string getPath();
		void onStart();
		void update();
		void onEnd();
		int getNextLevel();
		void setStartLocation(double & startX, double & startY);
	};
}