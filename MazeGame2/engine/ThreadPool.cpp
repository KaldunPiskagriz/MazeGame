#include "ThreadPool.hpp"
#include <format>
using namespace MultithreadingSystem;

void MultithreadingSystem::ThreadPool::ThreadFunc(const int& threadID, Logger* logger) {

	Task task([] {});
	std::string str;
	
	while (!isStopped) {

		std::unique_lock lock(taskQueueMutex);

		awake.wait(lock, [this] { return (!isPaused && !taskQueue.empty()); });

		if (!taskQueue.empty()) {

			task = std::move(taskQueue.front());
			taskQueue.pop();

			lock.unlock();

			str = "[ ThreadPool ]: Thread "; str.append(std::to_string(threadID)); str.append(" started executing task.");
			if (task.description != "") { str.append(" Task description: " + task.description); }
			logger->PrintMessage(str);

			threadsWorking++;
			task.action();

			str = "[ ThreadPool ]: Thread "; str.append(std::to_string(threadID)); str.append(" ended executing task.");
			logger->PrintMessage(str);
			threadsWorking--;

		}

	}

	str = "[ ThreadPool ]: Thread joined. id: "; str.append(std::to_string(threadID));
	logger->PrintMessage(str);

}

void MultithreadingSystem::ThreadPool::AddTask(const std::function<void()>& task, TaskType type, std::string description) {

	std::string str = "[ ThreadPool ]: Created new task";
	if (description != "") { str.append(". Description: " + description); }
	logger->PrintMessage(str);

	taskQueueMutex.lock();
	taskQueue.push(Task(task, type, description));
	taskQueueMutex.unlock();
	awake.notify_one();

}

void MultithreadingSystem::ThreadPool::CreateThread() {

	threadPoolMutex.lock();
	int id = GetNewID();
	threadPoolMutex.unlock();

	logger->PrintMessage(std::format("[ ThreadPool ]: Created new thread( id: {} )", id));

	std::lock_guard<std::mutex> guard(threadsVectorMutex);
	threadsVector.emplace_back(new std::thread(&ThreadPool::ThreadFunc, this, id, logger ));

}

int MultithreadingSystem::ThreadPool::CountThreads() {
	
	std::lock_guard<std::mutex> guard(threadsVectorMutex);
	return threadsVector.size();

}

MultithreadingSystem::ThreadPool::~ThreadPool() {
	isStopped = true;
	for (auto currentThread : threadsVector) {
		currentThread->join();
	}
	logger->PrintMessage("[ ThreadPool ]: All threads stopped, ThreaPool destroyed");
}
