#pragma once

#include <map>
#include "Texture.h"

namespace reflections {

	class TextureManager {
	private:
		static std::map<int, Texture*> textureMap;
	public:
		static bool loadTextures();
		static Texture * getTexture(int id);
		static void destroy();
	};
}