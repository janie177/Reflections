#include "Cooldown.h"
#include <chrono>

reflections::Cooldown::Cooldown(long long int millis) {
	this->millis = millis;
	last = 0;
}

reflections::Cooldown::Cooldown() {
	this->millis = 0;
	last = 0;
}

void reflections::Cooldown::set() {
	last = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

void reflections::Cooldown::clear() {
	last = 0;
}

void reflections::Cooldown::setLength(long long int millis) {
	this->millis = millis;
}

bool reflections::Cooldown::isCooledDown() {
	long long int current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	return current - last >= millis;
}

long long int reflections::Cooldown::getTimeRemaining() {
	long long int current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	return millis - (current - last);
}

long long int reflections::Cooldown::getCooldownTime() {
	return millis;
}

double reflections::Cooldown::getPct() {
	if (millis == 0) {
		return 1;
	}
	return (1.0 - ((double)getTimeRemaining() / (double)millis)) * 100;
}
