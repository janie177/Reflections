#pragma once
#include <map>
#include <functional>

namespace reflections {

	class World;

	class TaskManager {
	private:
		World * world;
		std::multimap<long long int, std::function<void()>> tasks;
	public:
		TaskManager(World * world);

		void scheduleTask(std::function<void()> task, long long int tickDelay);

		void execute();
	};
}