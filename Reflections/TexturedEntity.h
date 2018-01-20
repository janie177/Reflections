#pragma once
#include "Entity.h"
#include "Textured.h"

namespace reflections {

	class TexturedEntity : public Entity, public Textured {
	private:
	public:
		TexturedEntity(int x, int y, World & world, EntityType type, double speed, int width, int height, int textureID);
		virtual void updateAnimation() = 0;
	};
}