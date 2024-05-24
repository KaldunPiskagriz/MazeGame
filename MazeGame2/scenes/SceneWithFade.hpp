#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "../engine/Engine.hpp"

extern unsigned windowWidth;
extern unsigned windowHeight;

class SceneWithFade : public Scene {
protected:
	sf::RectangleShape rect{sf::Vector2f(windowWidth, windowHeight)};
	std::optional<bool> isFadingOut{ false };
	std::string targetSceneName;

	SceneWithFade() {
		rect.setFillColor(sf::Color(0, 0, 0, 255));
		activeGUI = nullptr;
	}

	void InternalDraw(sf::RenderWindow* window) {
		window->draw(rect);
	}

	void InternalTick() {
		if (isFadingOut.has_value()) {
			rect.setFillColor(sf::Color(0, 0, 0, std::clamp((isFadingOut.value() ? (rect.getFillColor().a + 10) : (rect.getFillColor().a - 10)), 0, 255)));
			if (isFadingOut.value() == false && rect.getFillColor().a == 0) {
				activeGUI = &GUI;
				SceneFadedInCallback();
				isFadingOut.reset();
			}
			else if (isFadingOut.value() && rect.getFillColor().a == 255) {
				activeGUI = &GUI;
				SceneControl::CreateSceneChangeRequest(SceneControl::SceneChangeRequest(SceneControl::Swap, targetSceneName));
				SceneFadedOutCallback();
				isFadingOut.reset();
			}
		}
	}

	void GoTo(const std::string& name) {
		targetSceneName = name;
		activeGUI = nullptr;
		isFadingOut = true;
	}

	virtual void SceneFadedInCallback() {  };
	virtual void SceneFadedOutCallback() {  };

};