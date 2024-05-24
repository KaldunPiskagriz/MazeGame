#include "SimpleButton.hpp"
#include "../../EngineVariables.hpp"


SimpleButton::SimpleButton(float xArg, float yArg, sf::String text, std::string fontName, unsigned int fontSize, std::function<void()> onClickArg, std::function<void()> onHoverArg, std::function<void()> onNotHoverArg) :
	posX(xArg),
	posY(yArg)
	{

	//sprites[" "];

	if (onClickArg == 0) {
		onClick = [] {};
	} else {
		onClick = onClickArg;
	}

	if (onHoverArg == 0) {
		onHover = [this] { this->buttonText.setFillColor(sf::Color(150, 150, 150)); };
	} else {
		onHover = onHoverArg;
	}

	if (onNotHoverArg == 0) {
		onNotHover = [this] { this->buttonText.setFillColor(sf::Color::White); };
	}
	else {
		onNotHover = onNotHoverArg;
	}

	EngineVariables* engineVariables = EngineVariables::GetInstance();
	buttonText.setFont(engineVariables->fonts[fontName]);

	buttonText.setString(text);
	buttonText.setCharacterSize(fontSize);

	buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
	buttonText.setPosition(xArg, yArg);
	bounds = buttonText.getGlobalBounds();


}

void SimpleButton::Draw(sf::RenderWindow* window) {
	//window->draw(sprites[selectedTexture].sprite);
	window->draw(buttonText);
}


void SimpleButton::OnHover() {
	onHover();
	isSelected = true;
}

void SimpleButton::OnNotHover() {
	onNotHover();
	isSelected = false;
}

sf::FloatRect SimpleButton::GetBounds() {
	return bounds;
}

void SimpleButton::SetText(const sf::String& text) {
	buttonText.setString(text);
	SetAlign(align);
	bounds = buttonText.getGlobalBounds();
}

void SimpleButton::SetAlign(alignType alignArg) {
	align = alignArg;
	if (align == center) {
		buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
	}
	else if (align == left) {
		buttonText.setOrigin(0, 0);
	}
}

void SimpleButton::OnClick() {
	onClick();
}
