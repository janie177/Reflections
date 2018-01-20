#include "Textured.h"

using namespace reflections;

reflections::Textured::Textured(int id) {
	textureData.setTexture(id);
}

TextureData & reflections::Textured::getTextureData() {
	return textureData;
}
