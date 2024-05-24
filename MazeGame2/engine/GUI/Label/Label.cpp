#include "Label.hpp"
#include "../../EngineVariables.hpp"

sf::FloatRect Label::GetBounds()
{
    return sf::FloatRect();
}

Label::Label(float xArg, float yArg, sf::String text, std::string fontName, unsigned int fontSize) 
    : posX(xArg), posY(yArg) {

    EngineVariables* engineVariables = EngineVariables::GetInstance();
    labelText.setFont(engineVariables->fonts[fontName]);
    labelText.setString(text);
    labelText.setCharacterSize(fontSize);
    labelText.setOrigin(labelText.getLocalBounds().width / 2, labelText.getLocalBounds().height / 2);
    labelText.setPosition(xArg, yArg);
    bounds = labelText.getGlobalBounds();
}

void Label::Draw(sf::RenderWindow* window) {
    window->draw(labelText);
}