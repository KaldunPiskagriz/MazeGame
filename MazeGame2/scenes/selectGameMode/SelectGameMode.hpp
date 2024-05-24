#pragma once
#include "../../engine/Engine.hpp"
#include "../SceneWithFade.hpp"

extern unsigned windowHeight;
extern unsigned windowWidth;

class GameModeSelectScene : public SceneWithFade {

public:

	GameModeSelectScene() : SceneWithFade() {
		
		TextsDB* texts = TextsDB::GetInstance();

		GUI.CreateLabel("Title", 0.5, 0.07, texts->GetText("game-mode-title"), "base", 0.1);
		static_cast<Label*>(GUI.GetElementByName("Title"))->labelText.setFillColor(sf::Color::White);

		GUI.CreateButton("Claasic", 0.5, 0.5, texts->GetText("game-mode-classic"), "base", 0.07,
			[this] { GoTo("gameClassic"); },
			0, 0);
	}

	void Tick(){
		
		InternalTick();
	}

	void Draw(sf::RenderWindow* window) {
		GUI.DrawGUI(window);
		InternalDraw(window);
	}

};