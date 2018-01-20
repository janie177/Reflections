#include "TextureData.h"
#include "TextureManager.h"
#include <iostream>

using namespace reflections;

void reflections::TextureData::update() {
	if (texture->getFrames() > 1) {
		tickCount++;
		if (tickCount >= texture->getTicksPerFrame()) {
			tickCount = 0;
			currentFrame++;
			if (currentFrame >= texture->getFrames()) {
				currentFrame = 0;
				if (nextTexture != -1) {
					setTexture(nextTexture);
					return;
				}
			}
		}
		position.x = currentFrame * texture->getFrameWidth();
	}
}

reflections::TextureData::TextureData() {

}

int reflections::TextureData::getID() {
	return id;
}


//Set the texture. If next is defined, switch to that texture after playing this animation cycle once.
void reflections::TextureData::setTexture(int id, int next) {
	//Only do anything if the ID changes.
	if (this->id == id) return;

	this->id = id;
	this->nextTexture = next;
	texture = TextureManager::getTexture(id);
	tickCount = 0;
	currentFrame = 0;
	//Commented out. Remember if flipped.
	//flip = SDL_FLIP_NONE;

	if (texture == nullptr) {
		std::cout << "Warning: attempting to set texture that doesn't exist. ID: " << id << "." << std::endl;
		return;
	}

	//Set the dimensions of the current sub texture.
	position.y = 0;
	position.w = texture->getFrameWidth();
	position.x = currentFrame * position.w;
	position.h = texture->getHeight();
}

Texture * reflections::TextureData::getTexture() {
	return texture;
}

SDL_Rect * reflections::TextureData::getFramePosition() {
	return &position;
}

SDL_RendererFlip reflections::TextureData::getFlip() {
	return flip;
}

void reflections::TextureData::setFlipped(bool flip) {
	this->flip = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}