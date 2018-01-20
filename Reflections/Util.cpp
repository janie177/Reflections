#include "Util.h"
#include "Chunk.h"

using namespace reflections;

int reflections::chunkFromX(double x) {
	return x / CHUNK_SIZE;
}

double reflections::worldXFromChunk(int chunkID) {
	return chunkID * CHUNK_SIZE;
}


