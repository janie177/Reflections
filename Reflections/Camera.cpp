#include "Camera.h"
#include "Level.h"
#include "GameManager.h"

#define CAMERA_MAX_DISTANCE 80

using namespace reflections;

//Class camera is a basic entity. It just needs to be passed a world to be created.
//Note that the world does not actually matter, it just has to be there since a camera has a location, even if its cross-dimension.
reflections::Camera::Camera(Level & level) : Entity(0, 0, level.getCurrentWorld(), CAMERA, 1, 0, 0) {

}

void reflections::Camera::updateCamera() {
	Location playerLoc = GameManager::getInstance().getLevelManager().getCurrentLevel()->getPlayer().virtualLocation();
	Location location = getLocation();

	//If the player changed world, set the cameras world as well.
	if (&playerLoc.getWorld() != &location.getWorld()) {
		location.setWorld(playerLoc.getWorld());
	}

	double dx = playerLoc.getX() - location.getX();
	double dy = playerLoc.getY() - location.getY();
	double difference;


	if (dx < -CAMERA_MAX_DISTANCE) {
		location.setX(playerLoc.getX() + CAMERA_MAX_DISTANCE);
	}
	else if (dx > CAMERA_MAX_DISTANCE) {
		location.setX(playerLoc.getX() - CAMERA_MAX_DISTANCE);
	}

	if (dy < -CAMERA_MAX_DISTANCE) {
		location.setY(playerLoc.getY() + CAMERA_MAX_DISTANCE);
	}
	else if (dy > CAMERA_MAX_DISTANCE) {
		location.setY(playerLoc.getY() - CAMERA_MAX_DISTANCE);
	}

	/*
	double absDx, absDy;
	absDx = abs(dx);
	absDy = abs(dy);

	//If camera is too far from the player, move it closer.
	if (absDx > CAMERA_MAX_DISTANCE) {
		difference = (absDx - CAMERA_MAX_DISTANCE) / 30;
		if (difference < 1) difference = 1;
		location.addX((dx < 0 ? -difference : difference));
	}
	if (absDy > CAMERA_MAX_DISTANCE) {
		difference = (absDy - CAMERA_MAX_DISTANCE) / 30;
		if (difference < 1) difference = 1;
		location.addY((dy < 0 ? -difference : difference));
	}
	*/


	Renderer & renderer = GameManager::getInstance().getRenderer();

	//Make sure camera cannot go too far to the left so that background will always cover the screen.
	double minX = renderer.getScreenWidth() / 2;
	double minY = renderer.getScreenHeight() / 2;
	if (location.getX() < minX) {
		location.setX(minX);
	}
	if (location.getY() < minY) {
		location.setY(minY);
	}

	//Set camera to new location.
	setLocation(location);
}
