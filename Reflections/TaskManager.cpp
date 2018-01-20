#include "TaskManager.h"
#include "GameManager.h"
#include <iterator>
#include <iostream>

reflections::TaskManager::TaskManager(World * world) {
	this->world = world;
}

//Schedule a lambda task for later execution.
//Multiple lambdas can be stored under the same key because of the multimap.
void reflections::TaskManager::scheduleTask(std::function<void()> task, long long int tickDelay) {
	long long int currentTick = world->getTick();
	tasks.insert(std::pair<long long int, std::function<void()>>((currentTick + tickDelay), task));
}

//Execute all scheduled lambda tasks. Map is automatically ordered so as soon as a tick is reached that's still not happened, stop the loop.
void reflections::TaskManager::execute() {
	long long int counter = 0;
	long long int currentTick = world->getTick();
	std::map<long long int, std::function<void()>>::iterator itr = tasks.begin();
	while (itr != tasks.end()) {

		counter = itr->first;
		if (counter > currentTick) {
			break;
		}
		counter = itr->first;

		try {
			(itr->second)();
		}
		catch (...) {
			std::cout << "Error while executing delayed task." << std::endl;
		}

		itr = tasks.erase(itr);
	}
}
