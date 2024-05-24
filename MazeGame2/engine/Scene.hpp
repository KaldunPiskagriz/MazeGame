#pragma once
#include <SFML/Graphics.hpp>
#include "GUI/BaseGUI.hpp"

// Basic scene class
class Scene {

protected:
	BaseGUI GUI;

public:

	BaseGUI* activeGUI{ &GUI };
	std::string name;

	virtual void Tick() = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;
	virtual void LocalHandleEvent(const sf::Event& event) {};
	virtual ~Scene() {};

};