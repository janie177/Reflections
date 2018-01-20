#pragma once
#include <SDL_image.h>
#include "Texture.h"

namespace reflections{

	class TextureData {
	private:
		SDL_Rect position;
		int id;
		Texture * texture;
		int currentFrame;
		int tickCount;
		int nextTexture;
		SDL_RendererFlip flip;
	public:
		TextureData();

		void update();
		int getID();
		void setTexture(int id, int next = -1);
		Texture * getTexture();
		SDL_Rect * getFramePosition();
		SDL_RendererFlip getFlip();
		void setFlipped(bool flip);
	};
}