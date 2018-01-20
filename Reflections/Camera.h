#pragma once
#include "Entity.h"

namespace reflections {

	//Camera keeps track of what parts of the world should be rendered.
	class Camera : public Entity {
	private:
	public:
		Camera(Level & level);
		void updateCamera();
	};
}

