#pragma once
#include "../../engine/Engine.hpp"
#include "../SceneWithFade.hpp"
#include <SFML/Graphics.hpp>

class VictoryScreen : public SceneWithFade {

public:

	void Tick() {

		InternalTick();
	}

	void Draw(sf::RenderWindow* window) {

		GUI.DrawGUI(window);
		InternalDraw(window);
	}

	VictoryScreen() : SceneWithFade() {
		GUI.CreateLabel("title", 0.5, 0.5, TextsDB::GetInstance()->GetText("victory-label"), "base", 0.1);
		static_cast<Label*>(GUI.GetElementByName("title"))->labelText.setFillColor(sf::Color::White);
	}
};