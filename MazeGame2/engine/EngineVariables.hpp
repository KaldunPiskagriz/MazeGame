#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.hpp"
#include <unordered_map>
#include <string>
#include <unordered_map>
#include "SceneChangeRequest.hpp"

class Scene;

class EngineVariables : public Singleton<EngineVariables> {

public:
	unsigned windowWidth{ 0 };
	unsigned windowHeight{ 0 };
	Scene* currentScene{ nullptr };
	std::string prevScene;
	unsigned long GlobalFrameTimer{ 0 };
	std::unordered_map<std::string, sf::Font> fonts;

	std::unordered_map<std::string, Scene*> loadedScenes;

	SceneControl::SceneChangeRequest sceneChangeRequest;

	void SetEngineVariables(unsigned windowWidthA, unsigned windowHeightA, Scene* currentSceneA);

};

//void EngineVariables::SetEngineVariables(unsigned windowWidthA, unsigned windowHeightA, Scene* currentSceneA, Scene* loadedSceneA, Mover* moverA) {
//	windowWidth = windowWidthA;
//	windowHeight = windowHeightA;
//	currentScene = currentSceneA;
//	loadedScene = loadedSceneA;
//	mover = moverA;
//}