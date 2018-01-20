#pragma once

#include "Sound.h"
#include <map>

/*
	TODO:  SOUND IS NOT IMPLEMENTED YET.
*/

namespace reflections {

	class SoundManager {
	private:
		//Map containing sound ID and sound
		std::map<int, Sound> sounds;
	public:
		SoundManager();
		
		//Methods to load all sounds and their ID's from file and destroy them again.
		bool load();
		void destroy();

		//Play the sound with the given ID, ONCE or on LOOP.
		//Volume 0-1
		//FadeIn/FadeOut in seconds.
		//This returns an int ID, which is a unique ID used to manipulate the sound playing.
		int playSound(int soundID, double volume, double fadeIn, double fadeOut);

		//Use the ID returned by playSound to stop the sound.
		//Returns true if the sound was playing and is now stopped.
		bool stopSound(int id);

		//Use the ID returned by playSound to pause or unpause.
		bool pause(int id);
		bool unPause(int id);
		bool toggle(int id);

		//Set sound volume with the ID returned by playSound
		bool setVolume(int id, double volume);

		//Pause or unpause all sounds.
		void pauseAll();
		void unPauseAll();

		//Remove all sounds currently playing.
		void stopAll();
	};


}