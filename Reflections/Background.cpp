#include "Background.h"
#include "GameManager.h"

using namespace reflections;

Background::Background(World * world, int back, int middle, int front, int close) {
	this->world = world;
	textures[0] = back;
	textures[1] = middle;
	textures[2] = front;
	textures[3] = close;
}

int reflections::Background::getTextureID(int index) {
	return textures[index];
}

double reflections::Background::getXOffset(int index, Location & cameraLocation) {
	return (cameraLocation.getX() - (GameManager::getInstance().getRenderer().getScreenWidth() / 2)) * getLayerMultiplier(index);
}

double reflections::Background::getYOffset(int index, Location & cameraLocation) {
	double offset = ((cameraLocation.getY() - (GameManager::getInstance().getRenderer().getScreenHeight() / 2)) * getLayerMultiplier(index));
	return offset < 0 ? 0 : offset;
}

double reflections::Background::getLayerMultiplier(int layer) {
	static const double speeds[4]{ 0.1, 0.5, 1.0, 1.8 };
	return speeds[layer];
}
