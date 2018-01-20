#include "TileBehaviour.h"

using namespace reflections;

//All behaviour const instances
const NeutralBehaviour TileBehaviour::NEUTRAL = NeutralBehaviour();
const DamageBehaviour TileBehaviour::DAMAGE = DamageBehaviour();


//Definitions of behaviour

void NeutralBehaviour::onCollide(Entity & entity) {
	//DO NOTHING HERE BECAUSE NEUTRAL
	//Maybe add a little marticle effect when you walk on a neutral block? Might look nice.
}

void DamageBehaviour::onCollide(Entity & entity) {
	//DAMAGE ENTITIY HERE
}
