#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

namespace reflections {

	//Class containing info about a texture and possible animation
	class Texture {
	private:
		int id;
		SDL_Texture * texture;
		std::string path;
		int frames;
		int width;
		int height;
		int frameWidth;
		int ticksPerFrame;
	public:
		Texture(int id, int frames, int ticksPerFrame, std::string path);
		~Texture();

		bool load();
		bool destroy();

		int getID();
		SDL_Texture* getTexture();
		int getFrames();
		int getFrameWidth();
		int getTicksPerFrame();
		int getWidth();
		int getHeight();
	};
}

