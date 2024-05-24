#pragma once
#include <string>
#include "SceneChangeRequest.hpp"
#include "Scene.hpp"

namespace SceneControl {

	void ChangeScene(std::string sceneName);
	void ReplaceScene(std::string sceneName);
	void SwapScene(std::string sceneName);
	void SwapScene(std::string sceneName, std::string newName);
	void DemandChange(SceneChangeRequest* request);
	void CreateSceneChangeRequest(SceneChangeRequest request);
	void ClearScene(std::string sceneName);
	void DeleteAndReplaceScene(std::string sceneName);

}