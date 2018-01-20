#include "Text.h"
#include "Renderer.h"
#include <SDL_image.h>
#include <iostream>
#include "GameManager.h"

using namespace reflections;

SDL_Texture * reflections::Text::getTexture() {
	return texture;
}

std::string reflections::Text::getText() {
	return text;
}

int reflections::Text::getR() {
	return r;
}

int reflections::Text::getG() {
	return g;
}

int reflections::Text::getB() {
	return b;
}

int reflections::Text::getWidth() {
	return width;
}

int reflections::Text::getHeight() {
	return height;
}

Text * reflections::Text::setWidth(int width) {
	this->width = width;
	return this;
}

Text * reflections::Text::setHeight(int height) {
	this->height = height;
	return this;
}

Text * reflections::Text::scale(double scale) {
	width *= scale;
	height *= scale;
	return this;
}

Text * reflections::Text::setRGB(double r, double g, double b) {
	this->r = r;
	this->g = g;
	this->b = b;
	return this;
}

Text * reflections::Text::setText(std::string text) {
	this->text = text;
	return this;
}

//Generate a new texture with the text and colors given.
bool reflections::Text::generate() {
	SDL_Surface * surface = nullptr;

	Renderer & renderer = GameManager::getInstance().getRenderer();

	SDL_Color color = { r, g, b };
	surface = TTF_RenderText_Solid(renderer.getFont(), text.c_str(), color);

	if (surface == nullptr) {
		return false;
	}

	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);

	SDL_FreeSurface(surface);

	if (texture == nullptr) {
		return false;
	}

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	return true;
}

void reflections::Text::destroy() {
	SDL_DestroyTexture(texture);
}

reflections::Text::Text() {
	text = "";
	r = 255;
	g = 255;
	b = 255;
	texture = nullptr;
	width = 0;
	height = 0;
}

reflections::Text::~Text() {
	destroy();
}

Text * reflections::Text::create(std::string str, int r, int g, int b) {
	Text * text = new Text();
	text->setRGB(r, g, b);
	text->setText(str);

	if (!text->generate()) {
		std::cout << "Error while trying to create Text from string: " << str << std::endl;
	}
	return text;
}
