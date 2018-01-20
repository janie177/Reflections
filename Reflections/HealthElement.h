#pragma once
#include "GUIElement.h"
#include "TextureManager.h"
#include <SDL.h>

namespace reflections {

	class HealthElement : GUIElement {
	private:
		Texture * texture;
		Texture * playerIcon;
	public:
		HealthElement();
		void renderElement();
	};
}