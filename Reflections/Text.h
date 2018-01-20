#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace reflections {

	class Text {
	private:
		std::string text;
		int r, g, b;
		SDL_Texture * texture;
		int width, height;

		//Private constructor. User Text::create();
		Text();
	public:
		SDL_Texture * getTexture();
		std::string getText();
		int getR();
		int getG();
		int getB();

		int getWidth();
		int getHeight();

		Text * setWidth(int width);
		Text * setHeight(int height);

		Text * scale(double scale);

		Text * setRGB(double r, double g, double b);
		Text * setText(std::string text);

		//Generate a texture from the input.
		bool generate();
		void destroy();

		~Text();

		//Static creation method
		static Text * create(std::string str, int r, int g, int b);
	};
}