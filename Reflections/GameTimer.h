#pragma once
#include <chrono>

namespace reflections {

	//This is a class that keeps track of time between frames and ticks in milliseconds.
	//I have chosen to put this in a class because it looks much cleaner in the game loop this way.
	class GameTimer {
	private:
		int fps;
		int tps;
		double tickDelay;
		double microsBetweenFrames;
		double microsBetweenTicks;
		double frameDelay;
		long long int tick;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastTick;
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
	public:
		GameTimer(int fps, int tps);
		void update();
		bool nextTick();
		bool nextFrame();

		//Get how far from the next tick we are
		double nextTickPct();
		double secondsSinceFrame();
		double secondsSinceTick();

		long long int getTick();
		double getActualFPS();
		double getActualTPS();
	};
}

