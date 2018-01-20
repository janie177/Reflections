#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Location.h"

namespace reflections {
	
	//Forward declare
	class Text;
	class GameManager;

	class Renderer {
	private:
		GameManager * manager;
		SDL_Window * window;
		SDL_Renderer * renderer;
		TTF_Font * font;
		int width;
		int height;
	public:
		Renderer(GameManager * manager);

		//Clear the screen and render a new frame for the active world.
		bool render();

		//Destroy created objects.
		bool quit();

		//Get a pointer to the SDL renderer.
		SDL_Renderer * getRenderer();

		//Get a pointer to the window.
		SDL_Window * getWindow();

		//Get height and width of the screen currently.
		double getScreenHeight();
		double getScreenWidth();

		//Get the font.
		TTF_Font * getFont();

		//Calculate where on the screen something should be rendered
		void translateLocation(Location & cameraLocation, int x, int y, int & screenX, int & screenY);

		//Init all SDL related things here.
		bool init();
	};
}

