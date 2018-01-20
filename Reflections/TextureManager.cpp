#include "TextureManager.h"
#include "FileReader.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace reflections;

//Static init of the registry
std::map<int, Texture*> TextureManager::textureMap;

bool reflections::TextureManager::loadTextures() {
	FileReader reader("Assets/Textures/Textures.dat");

	//Open the file and check for eventual exceptions.
	if (!reader.open()) {
		std::cout << "Error while loading textures file." << std::endl;
		return false;
	}

	//Loop through lines in the file.
	while (reader.nextLine()) {
		std::string line;
		int id, frames, ticksPerFrame;
		std::string path;

		line = reader.getCurrentLine();

		//Replace commas with spaces.
		std::replace(line.begin(), line.end(), ',', ' ');

		//Create a string stream from the raw line, and split it up into an ID and path.
		std::stringstream stream(line);
		stream >> id;
		stream >> path;
		stream >> frames;
		stream >> ticksPerFrame;

		//Create a new texture object.
		Texture * texture = new Texture(id, frames, ticksPerFrame, path);

		if (texture->load()) {
			textureMap[id] = texture;
		}
		else {
			delete texture;
			std::cout << "Could not load texture with ID: " << id << "." << std::endl;
		}
	}

	//Close file stream.
	reader.close();
	return true;
}

Texture * reflections::TextureManager::getTexture(int id) {
	if (textureMap.count(id) > 0) {
		return textureMap[id];
	}
	std::cout << "Trying to retrieve texture with ID: " << id << " which is not valid." << std::endl;
	return nullptr;
}

void reflections::TextureManager::destroy() {
	for (auto & texture : textureMap) {
		texture.second->destroy();
	}
	textureMap.clear();
}
