#pragma once

namespace reflections {

	class Cooldown {
	private:
		long long int millis;
		long long int last;
	public:
		Cooldown(long long int millis);
		Cooldown();
		void set();
		void clear();
		void setLength(long long int millis);
		bool isCooledDown();

		long long int getTimeRemaining();
		long long int getCooldownTime();
		double getPct();
	};
}