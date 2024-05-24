#include "EngineVariables.hpp"

void EngineVariables::SetEngineVariables(unsigned windowWidthA, unsigned windowHeightA, Scene* currentSceneA) {
	windowWidth = windowWidthA;
	windowHeight = windowHeightA;
	currentScene = currentSceneA;
	loadedScenes.clear();
}
