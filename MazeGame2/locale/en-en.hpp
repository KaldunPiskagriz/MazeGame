#pragma once
#include "../engine/Engine.hpp"

class EnLocale : public TextDBBase {
public:
	EnLocale() {
		//main menu
		base["main-menu-title"] = L"Maze Game";
		base["main-menu-start"] = L"Start";
		base["main-menu-exit"] = L"Exit";

		//game mode selection screen
		base["game-mode-title"] = L"Select game mode";
		base["game-mode-classic"] = L"Classic";

		//in-game
		base["level"] = L"Level: ";
		base["game-mode"] = L"Game mode: ";
		base["score"] = L"Score: ";
		base["time"] = L"Time: ";
		base["gen-type"] = L"Generation method: ";

		//Victory
		base["victory-label"] = L"Victory!";
	}
};