#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "World.h"
#include "Camera.h"

namespace reflections {

	/*
	* Each level has a state which will determine what happens when the game is paused.
	*/
	enum class LevelState {
		PLAYING,	//Level is being played as normal.
		NEXTLEVEL,	//Level is completed, and there's a next level available.
		WIN,		//Level is completed, and this is the last level.
		LOSE		//The player lost.
	};

	//A level contains a player (Which contains a camera in turn) and a list of worlds.
	class Level {
	private:
		LevelState currentState;
		Player * player;
		Camera * camera;
		World * currentWorld;
		std::vector<World*> worlds;
		double startX, startY;
	public:
		Level();
		virtual ~Level() = 0;

		bool load();
		bool destroy();

		//Virtual methods that allow lots of level customization.
		virtual std::string getPath() = 0;
		virtual void onStart() = 0;
		virtual void update() = 0;
		virtual void onEnd() = 0;
		virtual int getNextLevel() = 0;
		virtual void setStartLocation(double & startX, double & startY) = 0;

		Player & getPlayer();
		Camera & getCamera();

		void setLevelState(LevelState state);
		LevelState getLevelState();

		double getStartX();
		double getStartY();

		int getWorldCount();
		World * getWorld(int index);

		//Methods to set and get the current world.
		World & getCurrentWorld();
		bool setCurrentWorld(int index);

		//Friend function for loading the level
		friend bool loadLevel(Level & level);
	};
}

