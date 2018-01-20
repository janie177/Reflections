#pragma once

#include <SDL.h>
#include <SDL_mixer.h>


/*
	TODO:  SOUND IS NOT IMPLEMENTED YET
*/

namespace reflections {
	class Sound {
	private:
		static int ids;
		int id;
		int channel;
		double volume;
		int soundID;
		Sound();
	public:
		static Sound create();
	};
}