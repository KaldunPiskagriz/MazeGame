#include "SceneControl.hpp"
#include "EngineVariables.hpp"
#include "Logger.hpp"

class EngineVariables;

//unloads current scene and trying to replace it with <sceneName> scene in loaded scenes hashmap(pointer in hashmap is deleted)
void SceneControl::ChangeScene(std::string sceneName) {
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* engineLogger = Logger::GetInstance();
	if (!engineVariables->loadedScenes[sceneName]) {
		engineLogger->PrintError("Trying to change scene to " + sceneName + ", but it is nullptr");
		return;
	}
	engineVariables->prevScene = engineVariables->currentScene->name;
	delete engineVariables->currentScene;
	engineVariables->currentScene = engineVariables->loadedScenes[sceneName];
	engineVariables->loadedScenes.erase(sceneName);
}

//unloads current scene and trying to replace it with <sceneName> scene in loaded scenes hashmap(pointer in hashmap remains)
void SceneControl::ReplaceScene(std::string sceneName) {
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* engineLogger = Logger::GetInstance();
	if (!engineVariables->loadedScenes[sceneName]) {
		engineLogger->PrintError("Trying to change scene to " + sceneName + ", but it is nullptr");
		return;
	}
	engineVariables->currentScene = engineVariables->loadedScenes[sceneName];
}

//swap current scene with <sceneName> scene in loaded scenes hashmap
void SceneControl::SwapScene(std::string sceneName) {
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* engineLogger = Logger::GetInstance();
	if (!engineVariables->loadedScenes[sceneName]) {
		engineLogger->PrintError("Trying to change scene to " + sceneName + ", but it is nullptr");
		return;
	}
	Scene* temp = engineVariables->currentScene;
	engineVariables->currentScene = engineVariables->loadedScenes[sceneName];
	engineVariables->loadedScenes[sceneName] = temp;
}

//swap current scene with <sceneName> scene in loaded scenes hashmap an changes it's name there
void SceneControl::SwapScene(std::string sceneName, std::string newName) {
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* engineLogger = Logger::GetInstance();
	if (!engineVariables->loadedScenes[sceneName]) {
		engineLogger->PrintError("Trying to change scene to " + sceneName + ", but it is nullptr");
		return;
	}
	Scene* temp = engineVariables->currentScene;
	engineVariables->currentScene = engineVariables->loadedScenes[sceneName];
	engineVariables->loadedScenes.erase(sceneName);
	engineVariables->loadedScenes[newName] = temp;
}

//Unload current scene andd delete it's pointer in hasmap and replace it with new scene
void SceneControl::DeleteAndReplaceScene(std::string sceneName) {
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* engineLogger = Logger::GetInstance();
	if (!engineVariables->loadedScenes[sceneName]) {
		engineLogger->PrintError("Trying to work with scene " + sceneName + ", but it is nullptr");
		return;
	}
	engineVariables->loadedScenes.erase(engineVariables->currentScene->name);
	delete engineVariables->currentScene;
	engineVariables->currentScene = engineVariables->loadedScenes[sceneName];
}

void SceneControl::DemandChange(SceneChangeRequest* request) {
	if (request->type == NoNeed) { return; }
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	if (engineVariables->currentScene->activeGUI) { engineVariables->currentScene->activeGUI->ResetSelection(); }
	switch (request->type) {
	case Change:
		SceneControl::ChangeScene(request->sceneName);
		break;
	case Replace:
		ReplaceScene(request->sceneName);
		break;
	case Swap:
		SceneControl::SwapScene(request->sceneName);
		break;
	case SwapAndGiveNewName:
		SceneControl::SwapScene(request->sceneName, request->newName);
		break;
	case DeleteAndReplace:
		SceneControl::DeleteAndReplaceScene(request->sceneName);
		break;
	}
	request->type = NoNeed;
}

void SceneControl::CreateSceneChangeRequest(SceneChangeRequest request) {
	EngineVariables* engineVariables = EngineVariables::GetInstance();
	engineVariables->sceneChangeRequest = request;
}

void SceneControl::ClearScene(std::string sceneName) {

	EngineVariables* engineVariables = EngineVariables::GetInstance();
	Logger* engineLogger = Logger::GetInstance();
	if (!engineVariables->loadedScenes[sceneName]) {
		engineLogger->PrintError("Trying to change scene to " + sceneName + ", but it is nullptr");
		return;
	}
	delete engineVariables->loadedScenes[sceneName];
	engineVariables->loadedScenes.erase(sceneName);

}

