#pragma once

namespace reflections {

	//Forward declaration to prevent circular dependency
	class Entity;
	class Tile;
	enum BoxSide;

	//Interactable is a purely abstract class which defines interacting behaviour in entities.
	//When an entity inherits this class, it will have a way to react to collision and gravity.
	class Interactable {
	private:
	public:
		virtual void onCollide(Entity & entity) = 0;
		virtual void onCollide(Tile & tile, BoxSide side) = 0;
		virtual double gravityModifier() = 0;
	};
}