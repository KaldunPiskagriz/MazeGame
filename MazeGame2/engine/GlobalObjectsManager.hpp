#pragma once
#include "Singleton.hpp"
#include "SimpleGameObject.h"
#include "Logger.hpp"
#include <unordered_map>

class GlobalObjectsManager : public Singleton<GlobalObjectsManager> {

	std::unordered_map<std::string, SimpleGameObject*> objects;

public:

	void CreateObject(const std::string& name, SimpleGameObject* obj) { objects[name] = obj; }
	void DeleteObject(const std::string& name) { objects.erase(name); }
	SimpleGameObject* Get(const std::string& name) { 
		if (objects.contains(name)) {
			return objects[name];
		}
		else {
			Logger* logger = Logger::GetInstance();
			logger->PrintError("Global object with name \"" + name + "\" does't exist");
			return nullptr;
		}
	}
	~GlobalObjectsManager() {
		for (auto& i : objects) {
			delete i.second;
		}
	}

};