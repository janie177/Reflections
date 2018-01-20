#include "Texture.h"
#include "Renderer.h"
#include <map>
#include <iostream>
#include "GameManager.h"

using namespace reflections;

reflections::Texture::Texture(int id, int frames, int ticksPerFrame, std::string path) {
	this->path = path;
	this->id = id;
	this->frames = frames;
	this->ticksPerFrame = ticksPerFrame;
	frameWidth = 0;
	width = 0;
	height = 0;
}

reflections::Texture::~Texture() {
	destroy();
}

bool reflections::Texture::load() {

	std::string fullPath = "Assets/Textures/" + path;

	SDL_Renderer * renderer = GameManager::getInstance().getRenderer().getRenderer();
	SDL_Texture * texture = nullptr;
	SDL_Surface * surface = IMG_Load(fullPath.c_str());

	if (surface == nullptr) {
		std::cout << "Could not load texture at path " << fullPath << "." << std::endl << IMG_GetError() << std::endl;
		SDL_FreeSurface(surface);
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		std::cout << "Could not load texture from SDL surface." << std::endl;
		SDL_FreeSurface(surface);
		return false;
	}

	this->texture = texture;

	//Set the dimensions of the current sub texture.
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	this->frameWidth = width / frames;

	SDL_FreeSurface(surface);
	return true;
}

//Destroy the created texture.
bool reflections::Texture::destroy() {
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;
	return true;
}

//Get the texture ID
int reflections::Texture::getID() {
	return id;
}

//Get the SDL texture pointer
SDL_Texture * reflections::Texture::getTexture() {
	return texture;
}

int reflections::Texture::getFrames() {
	return frames;
}

int reflections::Texture::getFrameWidth() {
	return frameWidth;
}

int reflections::Texture::getTicksPerFrame() {
	return ticksPerFrame;
}

int reflections::Texture::getWidth() {
	return width;
}

int reflections::Texture::getHeight() {
	return height;
}