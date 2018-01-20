#pragma once

namespace reflections {

	//This class contains some useful methods to perform calculations that are used in multiple places

	//Calculate the chunk based on an X coordinate.
	int chunkFromX(double x);

	double worldXFromChunk(int chunkID);
}