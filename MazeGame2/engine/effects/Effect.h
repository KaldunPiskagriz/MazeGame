#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Effect {
public:
	virtual void ApplyEffect(sf::Sprite &sprite, float x, float y) = 0;
	virtual ~Effect();
};