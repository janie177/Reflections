/*
	ABOUT:

	This is my take on the intake assignment for IGAD.
	Theme: Reflections
	Author: Jan Kind

	I'm using the SDL (Simple DirectMedia Layer) library for rendering and user input.
	I also depend on SDL's SDL_image library for hardware accelerated rendering (which in turn uses OpenGL).

	I was planning on also using SDL's sound mixer library, but ended up not implementing sound.

	I have previous experience in creating 2D games in Java, and I have created a basic 3d voxel engine in Java as well.
	For those I used both CPU rendering and OpenGL.
	
	This is my first time making a game in C++. Therefore this is also my first time working with SDL (Was recommended to me by a student at IGAD).
	During the course of creating this project, I learned alot of new things about both C++ and game developing.
	If I had to start over, there would be numerous things I'd change. 

	For this project I have made use of the following resources:
	- https://wiki.libsdl.org				#Basic SDL functionality, such as how to load an image and then display it on the screen.
	- http://www.cplusplus.com/reference	#Reference to std functions and data types that I make use of.
	- https://stackoverflow.com				#General C++ related questions and debugging purposes.
	- http://lazyfoo.net					#Tutorials on setting up SDL and how to use certain functions.		


	GAMEPLAY AND THEME:

	The game is a 2D side-scroller, in which you control the player character. The game has multiple levels, each of which contains multiple worlds.
	All worlds within a level are connected to eachother. You could say that the worlds are reflections of eachother.
	The player can freely travel between worlds during gameplay. This is the most important feature of the game.
	The players position and velocity is persistent across worlds. This allows me to make levels in which you have to parkour your way between separate worlds.

	Levels are designed in such a way that you need to travel between multiple worlds in order to make it to the next level.


	PROJECT STRUCTURE:

	The singleton class GameManager contains all relevant game information. It can be accessed anywhere to gain access to the player for example.
	The Renderer class is used for almost all rendering.
	Game.cpp contains the game loops, framerate control and ticks per second control.

	I made a FileLoader to allow me to load levels from a .dat file, and also load in textures from file.
	
	The LevelManager class (instanced in GameManager) handles levels. Each level contains multiple worlds.
	World.cpp contains methods for adding entities, tiles and updating them.
	In World.cpp, the onUpdateTick method handles entity interaction, velocity updating, gravity and collision detection.

	I made a simple particle system which can be found in ParticleEffect.cpp and Particle.cpp.
	There's multiple types of effects, each of which has their own class.

	I also made an abstract Entity system. Entity.cpp is the base class which is inherited by the others.
	Each entity has a type which is defined in Entity.h.
	
	The world exists out of chunks, which in turn contain tiles. Chunks reduce the amount of tiles that needs to be looped over
	when checking for collisions etc.

	Textures are defined in Assets/Textures/Textures.dat
	In this file, each texture gets an ID and is then loaded from the path provided.
	It also controls how many frames each texture has and how often the frames update.

	There's some other stuff like Text rendering, interpolating entity locations for smoother movement, GUI, Delayed tasks and the Menu.
	Those can all be found in the source.


	ART:

	The art in the game was partially done by my sister, and partially made by me. If it looks good, my sister made it. If it looks like someone used MS Paint,
	it's probably mine.
*/



//Include SDL here because it needs to init and override the main method.
#include <SDL.h>
#include <iostream>
#include "Game.h"
#include "GameManager.h"

using namespace reflections;

int main(int argc, char *argv[]) {

	int exitCode;

	//Reference to the game manager.
	GameManager & manager = GameManager::getInstance();

	//Init SDL and then load all textures in textures.dat. If anything goes wrong, exit the program.
	if (manager.init()) {
		//Run the game in the Game class. Returns the exit code. 
		exitCode = run();
	}
	else {
		exitCode = 1;
	}

	//Free allocated memory again.
	manager.destroy();

	std::cout << SDL_GetError() << std::endl;

	return exitCode;
}