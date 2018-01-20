#pragma once
#include "TextureData.h"

namespace reflections {

	class Textured {
	private:
		TextureData textureData;
	public:
		Textured(int id);

		TextureData & getTextureData();
	};
}