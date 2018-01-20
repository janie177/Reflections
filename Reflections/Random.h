#pragma once

namespace reflections {

	class Random {
	private:
	public:
		Random();
		static Random getInstance();
		double randomDouble(double min, double max);
		int randomInt(int min, int max);
	};
}