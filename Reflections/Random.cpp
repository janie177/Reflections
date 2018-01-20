#include "Random.h"
#include <random>
#include <ctime>

using namespace reflections;

reflections::Random::Random() {
	srand(time(NULL));
}

Random reflections::Random::getInstance() {
	static Random random;
	return random;
}

double reflections::Random::randomDouble(double min, double max) {
	return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}

int reflections::Random::randomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}
