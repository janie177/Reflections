/*
	This is the Renderer class.
	Almost all rendering is done here.
	I tried to separate SDL from the game logic as much as possible.
*/

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Util.h"
#include "Chunk.h"
#include "Tile.h"
#include "TextEntity.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "ParticleManager.h"

using namespace reflections;

reflections::Renderer::Renderer(GameManager * manager) {
	this->manager = manager;
	window = nullptr;
	renderer = nullptr;
	font = nullptr;
	width = 1024;
	height = 576;
}

bool reflections::Renderer::render() {
	//Clear the screen if the game is not set to paused.
	if (manager->getGameState() != PAUSED) {
		SDL_RenderClear(renderer);
	}
	
	//Local variables that will be reused.
	int chunkMin, chunkMax, i, j;

	//Rectangles SDL uses to render stuff on the screen.
	SDL_Rect srcRect, destRect;

	//The menu
	Menu & menu = manager->getMenu();

	//Draw the menu on the screen.
	if (manager->getGameState() == MENU) {

		//Draw the menu background
		SDL_RenderCopy(renderer, TextureManager::getTexture(manager->getMenu().getBackgroundID())->getTexture(), NULL, NULL);

		//Menu related options.
		int buttonTexID;
		destRect.w = menu.getButtonWidth();
		destRect.h = menu.getButtonHeight();
		destRect.x = (width / 2) - (destRect.w / 2);

		//Draw the buttons
		for (i = 0; i < MENU_OPTION_LENGTH; i++) {
			if (menu.getSelected() == i) {
				buttonTexID = menu.getSelectedTextureID((MenuOption)i);
			}
			else {
				buttonTexID = menu.getTextureID((MenuOption)i);
			}

			destRect.y = menu.getTopOffset() + ((menu.getButtonHeight() + menu.getSpaceBetweenButtons()) * i);
			SDL_RenderCopy(renderer, TextureManager::getTexture(buttonTexID)->getTexture(), NULL, &destRect);
		}
	}
	//Else draw the game on the screen.
	else if(manager->getGameState() == PLAYING) {

		//If no level is loaded don't render.
		if(manager->getLevelManager().getCurrentLevel() == nullptr) {
			return false;
		}

		//Retrieving references to useful data.
		Camera & camera = manager->getLevelManager().getCurrentLevel()->getCamera();

		//Update the camera location.
		camera.updateCamera();

		Location & cameraLocation = camera.getLocation();

		//References to required data.
		World & world = manager->getLevelManager().getCurrentLevel()->getCurrentWorld();
		Background & background = world.getBackground();

		//Calculate which chunks are visible.
		chunkMin = chunkFromX(cameraLocation.getX() - width / 1.9);
		chunkMax = chunkFromX(cameraLocation.getX() + width / 1.9);

		//Get the amount of seconds since the last frame (as a double)
		double dt = manager->getGameTimer().secondsSinceFrame();

		//Stuff required for rendering.
		Texture * texture = nullptr;
		double yOffset = 0;
		srcRect.h = height;
		srcRect.w = width;
		destRect.h = height;
		destRect.w = width;

		//Loop through background layers. Insert the world after layer 2.
		for (i = 0; i < 4; i++) {
			texture = TextureManager::getTexture(background.getTextureID(i));
			if (texture != nullptr) {

				srcRect.x = background.getXOffset(i, cameraLocation);
				yOffset = background.getYOffset(i, cameraLocation);
				srcRect.y = texture->getHeight() - height - yOffset;
				destRect.y = 0;
				destRect.x = 0;
				srcRect.h = height;
				srcRect.w = width;
				destRect.h = height;
				destRect.w = width;

				if (srcRect.y < 0) {
					destRect.y = -srcRect.y;
					srcRect.y = 0;
				}

				int maxX = texture->getWidth() - width;
				if (srcRect.x > maxX) {
					destRect.x = -(srcRect.x - maxX);
					srcRect.x = maxX;
				}

				SDL_RenderCopy(renderer, texture->getTexture(), &srcRect, &destRect);
			}

			//If layer is 2, insert all the world stuff. This is the main layer that moves at 1.0 speed.
			if (i == 2) {
				//Draw tiles on the screen
				for (j = chunkMin; j <= chunkMax; j++) {
					Chunk * chunk = world.getChunkAtIndex(j);
					if (chunk != nullptr) {
						for (Tile* & tile : *chunk->getTiles()) {

							if (tile == nullptr) {
								continue;
							}

							TileType & type = tile->getType();
							//Calculate the localX and localY values for this tile.
							translateLocation(cameraLocation, tile->getXOffset(), tile->getYOffset(), destRect.x, destRect.y);

							//Set the values in the rectangle for rendering
							destRect.h = type.getHeight();
							destRect.w = type.getWidth();

							TextureData & tData = type.getTextureData();
							//Draw the tile on the screen.
							SDL_RenderCopyEx(renderer, tData.getTexture()->getTexture(), tData.getFramePosition(), &destRect, 0, NULL, tData.getFlip());
						}
					}
				}

				//Pointer to textured entity for dynamic cast
				TexturedEntity * textured = nullptr;
				TextEntity * text = nullptr;
				bool inRange;
				int chunk;

				//Draw Entities on the screen.
				for (Entity* & entity : *world.getEntities()) {
					if (entity == nullptr) {
						continue;
					}
					chunk = entity->getLocation().getChunk();
					inRange = chunk >= chunkMin - 2 && chunk <= chunkMax + 2;
					//Make sure entity is nearby, and that entity has either a texture or text to display. Otherwise it can't be rendered.
					if (inRange && ((textured = dynamic_cast<TexturedEntity*>(entity)) != nullptr || (text = dynamic_cast<TextEntity*>(entity)) != nullptr)) {
						//Get interpolated location for the entity.
						Location interp = entity->virtualLocation();
						interp.addX(-(entity->getWidth() / 2));
						interp.addY((entity->getHeight()));

						translateLocation(cameraLocation, interp.getX(), interp.getY(), destRect.x, destRect.y);
						destRect.h = entity->getHeight();
						destRect.w = entity->getWidth();

						//IMPORTANT: Order of dynamic casts and order of checking here is important. When adding in different types of entity, keep the order the same.

						//If entity has a texture.
						if (textured != nullptr) {
							TextureData & tData = textured->getTextureData();
							SDL_RenderCopyEx(renderer, tData.getTexture()->getTexture(), tData.getFramePosition(), &destRect, 0, NULL, tData.getFlip());
						}
						//Otherwise entity has text
						else {
							int heightOffset = 0;
							int x = destRect.x;
							int y = destRect.y;
							for (Text* & line : text->getText()) {

								destRect.x = x - line->getWidth() / 2;
								destRect.y = y + heightOffset;
								destRect.w = line->getWidth();
								destRect.h = line->getHeight();

								SDL_RenderCopy(renderer, line->getTexture(), NULL, &destRect);

								//Increase height offset.
								heightOffset += line->getHeight();
							}
						}
					}
				}
			}
			//After rendering everything, add the particles on top.
			world.renderParticles(i, renderer, dt, cameraLocation.getX(), cameraLocation.getY());
		}
		//And lasttly on top of everything else, draw the GUI.
		manager->getGUI().render();
	}
	//Get the pause menu and display the correct text.
	else if (manager->getGameState() == PAUSED) {
		PauseMenu & pauseMenu = manager->getPauseMenu();
		Text * text = pauseMenu.getText(manager->getLevelManager().getCurrentLevel()->getLevelState());

		//Display the text centered in the screen.
		destRect.w = text->getWidth();
		destRect.h = text->getHeight();
		destRect.y = (height / 2) - destRect.h / 2;
		destRect.x = (width / 2) - destRect.w / 2;
		SDL_RenderCopy(renderer, text->getTexture(), NULL, &destRect);

		double scrX = width / 4;
		for (int j = 0; j < 2; j++) {
			Texture * button = TextureManager::getTexture(pauseMenu.getTexture((MenuButton)j));
			//Display the buttons at 25% height and at 25 and 75% width.
			destRect.w = button->getWidth();
			destRect.h = button->getHeight();
			destRect.y = (height * 0.75);
			destRect.x = scrX - destRect.w / 2;
			SDL_RenderCopy(renderer, button->getTexture(), NULL, &destRect);
			scrX *= 3;
		}

	}

	//Smear it all on the screen.
	SDL_RenderPresent(renderer);
	return true;
}

bool reflections::Renderer::init() {

	//Init SDL, and close with error if something went wrong
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Could not init SDL." << std::endl;
		return false;
	}

	//Create the window, and if something goes wrong exit the program.
	window = SDL_CreateWindow("Reflections", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "Could not create SDL window." << std::endl;
		return false;
	}

	//Create the SDL renderer, used drawing on the screen.
	//Vsync solves screen tear, but creates a stuttering issue because of the delay between displaying and calculating entity locations.
	//Software renderer has a bug in it where flipping a texture rendered at 100% of its resolution results in an access violation when
	//the texture is rendered as a sub-texture with more than 3 frames.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "Error occurred while creating SDL renderer." << std::endl;
		return false;
	}

	//Init the font rendering stuff.
	if (TTF_Init() != 0) {
		std::cout << "Could not enable SDL TTF." << std::endl;
		return false;
	}

	//Load the font for the game
	font = TTF_OpenFont("Assets/Fonts/font.ttf", 22);

	if (font == nullptr) {
		std::cout << "Failed to load game font." << std::endl;
		return false;
	}

	//Default screen color. Black.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//Set window to full screen.
	//Currently this causes a small bug with entities and particles moving rapidly.
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	SDL_RenderSetLogicalSize(renderer, width, height);

	//Return true when all went well, and the game loop will start.
	return true;
}

//Destroy created SDL context
bool reflections::Renderer::quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	SDL_Quit();
	return true;
}

SDL_Renderer * reflections::Renderer::getRenderer() {
	return renderer;
}

SDL_Window * reflections::Renderer::getWindow() {
	return window;
}

double reflections::Renderer::getScreenHeight() {
	return height;
}

double reflections::Renderer::getScreenWidth() {
	return width;
}

TTF_Font * reflections::Renderer::getFont() {
	return font;
}

//Translate a location in the world to a location on the screen.
void reflections::Renderer::translateLocation(Location & cameraLocation, int x, int y, int & screenX, int & screenY) {
	screenX = x - (cameraLocation.getX() - (width / 2));
	screenY = height - (y - (cameraLocation.getY() - (height / 2)));
}
