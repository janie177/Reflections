#pragma once
#include "Location.h"

namespace reflections {

	//Forward declaration
	class World;

	//The background class is rendered in the... you'll never guess it.
	//It contains three ints which correspond with an SDL_Texture pointer in the Texture source file.
	//Again, I choose ints to store textures so that I can keep most of the SDL stuff centralized.
	class Background {
	private:
		World * world;
		int textures[4];
	public:
		Background(World * world, int back, int middle, int front, int close);
		int getTextureID(int index);
		double getXOffset(int index, Location & cameraLocation);
		double getYOffset(int index, Location & cameraLocation);

		static double getLayerMultiplier(int layer);
	};
}