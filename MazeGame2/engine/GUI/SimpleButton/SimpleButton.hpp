#pragma once
#include "../GUIelement.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <string>

class SimpleButton : public GUIelement{

public:
	enum alignType { center, left };
private:

	/*struct buttonImage {
		sf::Texture texture;
		sf::Sprite sprite;
		inline buttonImage() { sprite.setTexture(texture); }
	};

	std::unordered_map<std::string, buttonImage> sprites;
	std::string selectedTexture{ " " };*/
	bool isSelected{ false };
	alignType align{ center };
	sf::FloatRect bounds;

	std::function<void()> onClick;
	std::function<void()> onHover;
	std::function<void()> onNotHover;

public:
	sf::Text buttonText;

	float posX{ 0 }, posY{ 0 };

	SimpleButton(float xArg, float yArg, sf::String text, std::string fontName, unsigned int fontSize, std::function<void()> onClickArg, std::function<void()>onHoverArg, std::function<void()> onNotHoverArg);
	virtual ~SimpleButton() {};
	void Draw(sf::RenderWindow* window);
	void OnHover();
	void OnNotHover();
	sf::FloatRect GetBounds();
	void SetText(const sf::String& text);
	void SetAlign(alignType alignArg);

	void OnClick();

};