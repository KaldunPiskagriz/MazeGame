#pragma once
#include "../GUIelement.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Label : public GUIelement {

	/*struct LabelImage {
		sf::Texture texture;
		sf::Sprite sprite;
		LabelImage() { sprite.setTexture(texture); }
	};*/

	sf::FloatRect bounds;

public:

	float posX{ 0 }, posY{ 0 };
	sf::Text labelText;

	sf::FloatRect GetBounds();
	Label(float xArg, float yArg, sf::String text, std::string fontName, unsigned int fontSize);
	~Label() {};
	void OnClick() {};
	void OnHover() {};
	void OnNotHover() {};
	void Draw(sf::RenderWindow* window);

};