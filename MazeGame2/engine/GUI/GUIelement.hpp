#pragma once
#include <SFML/Graphics.hpp>

class GUIelement {

public:

	virtual sf::FloatRect GetBounds() = 0;
	virtual void OnClick() = 0;
	virtual void OnHover() = 0;
	virtual void OnNotHover() = 0;
	virtual void Draw(sf::RenderWindow *window) = 0;
	virtual ~GUIelement() {};

};