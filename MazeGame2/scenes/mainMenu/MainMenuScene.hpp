#pragma once
#include "../../engine/Engine.hpp"
#include "../SceneWithFade.hpp"

extern unsigned windowHeight;
extern unsigned windowWidth;

class MainMenuScene : public SceneWithFade {

public:

	MainMenuScene() : SceneWithFade() {
		name = "mainMenu";
		TextsDB* texts = TextsDB::GetInstance();
		
		GUI.CreateLabel("Title", 0.5, 0.07, texts->GetText("main-menu-title"), "base", 0.1);
		static_cast<Label*>(GUI.GetElementByName("Title"))->labelText.setFillColor(sf::Color::White);

		GUI.CreateButton("Exit", 0.5, 0.8, texts->GetText("main-menu-exit"), "base", 0.07, 
			[] { exit(0); }, 0, 0);

		GUI.CreateButton("Start", 0.5, 0.6, texts->GetText("main-menu-start"), "base", 0.07,
			[this] { GoTo("selectGameMode"); }, 0, 0);

		rect.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void Tick() {
		InternalTick();
	}

	void Draw(sf::RenderWindow* window) {
		GUI.DrawGUI(window);
		InternalDraw(window);
	}

};