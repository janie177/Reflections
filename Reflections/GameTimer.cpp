#include "GameTimer.h"

using namespace reflections;

//Constructor which automatically calculates how long to wait between ticks and frames.
//Use microseconds for good accuracy.
GameTimer::GameTimer(int fps, int tps) {
	this->fps = fps;
	this->tps = tps;
	frameDelay = 1000000/ fps;
	tickDelay = 1000000 / tps;
	microsBetweenFrames = 1000000;
	microsBetweenTicks = 1000000;
	currentTime = std::chrono::high_resolution_clock::now();
	lastFrame = std::chrono::high_resolution_clock::now();
	lastTick = std::chrono::high_resolution_clock::now();
}

//Method which updates the current time inside the class.
void GameTimer::update() {
	currentTime = std::chrono::high_resolution_clock::now();
}

//Method that checks if enough time has passed for the next frame to be rendered.
//Automatically updates the last frame time when that happens.
bool GameTimer::nextFrame() {
	double micros = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastFrame).count();
	if (micros >= frameDelay) {
		microsBetweenFrames = micros;
		lastFrame = currentTime;
		return true;
	}
	return false;
}

//See how far we are from the next tick. 1.0 is there, 0.0 is not there at all.
double reflections::GameTimer::nextTickPct() {
	double microsSinceTick = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTick).count();
	return microsSinceTick / (double) microsBetweenTicks;
}

double reflections::GameTimer::secondsSinceFrame() {
	return (double)microsBetweenFrames / 1000000.0;
}

double reflections::GameTimer::secondsSinceTick() {
	return (double)microsBetweenTicks / 1000000.0;
}

long long int GameTimer::getTick() {
	return tick;
}

double reflections::GameTimer::getActualFPS() {
	return 1000000.0 / microsBetweenFrames;
}

double reflections::GameTimer::getActualTPS() {
	return 1000000.0 / microsBetweenTicks;
}

bool GameTimer::nextTick() {
	double micros = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTick).count();
	if (micros >= tickDelay) {
		microsBetweenTicks = micros;
		lastTick = currentTime;
		tick++;
		return true;
	}
	return false;
}