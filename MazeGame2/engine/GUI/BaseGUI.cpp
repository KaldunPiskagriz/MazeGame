#include "BaseGUI.hpp"

extern unsigned windowWidth;
extern unsigned windowHeight;

BaseGUI::BaseGUI() {
	elements.clear();
}

BaseGUI::~BaseGUI() {
	for (auto i : elements) {
		delete i.second;
	}
}

void BaseGUI::CreateButton(const std::string& name, float xArg, float yArg, sf::String text, std::string fontName, float fontSize, std::function<void()> onClickArg, std::function<void()> onHoverArg, std::function<void()> onNotHoverArg) {
	elements[name] = new SimpleButton(windowWidth * xArg, windowHeight * yArg, text, fontName, windowHeight * fontSize, onClickArg, onHoverArg, onNotHoverArg);
}

void BaseGUI::CreateLabel(const std::string& name, float xArg, float yArg, sf::String text, std::string fontName, float fontSize) {
	elements[name] = new Label(windowWidth * xArg, windowHeight * yArg, text, fontName, windowHeight * fontSize);
}

GUIelement* BaseGUI::GetElementByName(const std::string& name) {
	if (elements.contains(name)) {
		return elements[name];
	}
	else {
		Logger::GetInstance()->PrintError("[ BaseGUI ]: Element with name \"" + name + "\" does't exist");
		return nullptr;
	}
}


void BaseGUI::DrawGUI(sf::RenderWindow* window) {
	for (auto i : elements) {
		i.second->Draw(window);
	}
}

void BaseGUI::CheckSelection(float x, float y) {
	ResetSelection();
	for (auto i : elements) {
		if (i.second->GetBounds().contains(x, y)) {
			i.second->OnHover();
			selectedOne = i.second;
			break;
		}
	}
}

void BaseGUI::OnCLick() {
	if (selectedOne) { selectedOne->OnClick(); }
}
