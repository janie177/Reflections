#pragma once
#include "Entity.h"

namespace reflections {

	//TileBehaviour is a purely abstract class which will define how a tile behaves when certain events occur.
	class TileBehaviour {
	public:
		//Keep const instances of each type.
		const static NeutralBehaviour NEUTRAL;
		const static DamageBehaviour DAMAGE;

		//Inline empty function so it has a default that does nothing.
		virtual void onCollide(Entity & entity) {};

		//Purely virtual destructor with inline definition (no instance of TileBehaviour can be made, and child classes do not need to override).
		virtual ~TileBehaviour() = 0 {};
	};

	class NeutralBehaviour : public TileBehaviour {
		void onCollide(Entity & entity);
	};

	class DamageBehaviour : public TileBehaviour {
		void onCollide(Entity & entity);
	};
}