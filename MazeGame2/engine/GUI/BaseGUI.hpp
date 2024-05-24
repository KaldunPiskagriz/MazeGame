#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "SimpleButton/SimpleButton.hpp"
#include "Label/Label.hpp"
#include "GUIelement.hpp"
#include "../Logger.hpp"

class BaseGUI {

	GUIelement* selectedOne{ nullptr };

public:

	std::unordered_map<std::string, GUIelement*> elements;

	BaseGUI();
	~BaseGUI();
	void CreateButton(const std::string& name, float xArg, float yArg, sf::String text, std::string fontName, float fontSize, std::function<void()> onClickArg = [] {}, std::function<void()> onHoverArg = [] {}, std::function<void()> onNotHoverArg = [] {});
	void CreateLabel(const std::string& name, float xArg, float yArg, sf::String text, std::string fontName, float fontSize);
	GUIelement* GetElementByName(const std::string& name);
	void DrawGUI(sf::RenderWindow* window);
	void CheckSelection(float x, float y);
	void OnCLick();
	void ResetSelection() { if (selectedOne) { selectedOne->OnNotHover(); selectedOne = nullptr; } }

};