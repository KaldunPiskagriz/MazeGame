#pragma once
#include "Singleton.hpp"
#include "Logger.hpp"
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <string>

namespace MultithreadingSystem {

	enum TaskStatus { indle, processing, completed };
	enum TaskType { loading, other };

	struct Task {

		TaskStatus status{ MultithreadingSystem::indle };
		TaskType type{ other };
		std::string description;
		std::function<void()> action;

		Task(const std::function<void()>& action, TaskType type = other, std::string description = "") : action(action), description(description), type(type) {}
	};

	class ThreadPool : public Singleton<ThreadPool> {

		std::atomic<bool> isStopped{ false };
		std::atomic<bool> isPaused{ false };
		std::queue<Task> taskQueue;
		std::vector<std::thread*> threadsVector;
		std::atomic<int> lastThreadID{ -1 };

		std::mutex taskQueueMutex;
		std::mutex threadsVectorMutex;
		std::mutex loggerMutex;
		std::mutex threadPoolMutex;
		std::condition_variable awake;
		Logger* logger = Logger::GetInstance();

		void ThreadFunc(const int& threadID, Logger* logger);
		int GetNewID() { lastThreadID += 1; return lastThreadID; }
		std::atomic<int> threadsWorking{ 0 };

	public:

		void AddTask( const std::function<void()> &task, TaskType type, std::string description = "");
		void CreateThread();
		int CountThreads();
		void Stop() { isStopped = true; }
		~ThreadPool();

		//return false if threadpool is idle
		bool GetStatus() { return ( !( !threadsWorking && taskQueue.empty() ) ); }
	};


}