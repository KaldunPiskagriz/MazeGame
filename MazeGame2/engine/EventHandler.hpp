#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include "EngineVariables.hpp"
#include "Scene.hpp"
#include "Singleton.hpp"

class EventHandler : public Singleton<EventHandler> {
	
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* logger = Logger::GetInstance();
	sf::RenderWindow* target;
	std::mutex mutex;

	struct microEvent {
		std::function<void(const sf::Event&)> func;
		sf::Event::EventType type;
		microEvent(std::function<void(const sf::Event&)> func, const sf::Event::EventType& type) : func(func), type(type){}
	};

	std::vector<microEvent> listeners;

public:
	
	void HandleEvent(const sf::Event& event, std::unordered_map<std::string, int>& settings);
	void SetTarget(sf::RenderWindow* targetArg) { target = targetArg; }
	void RegisterEventListener(std::function<void(const sf::Event&)> func, const sf::Event::EventType& type) {
		mutex.lock();
		listeners.emplace_back(microEvent(func, type));
		mutex.unlock();
	}
	
};