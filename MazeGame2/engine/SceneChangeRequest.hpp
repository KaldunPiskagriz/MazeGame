#pragma once
#include <string>

namespace SceneControl {

	enum SceneChangeType { NoNeed, Change, Swap, SwapAndGiveNewName, Replace, DeleteAndReplace };

	struct SceneChangeRequest {


		SceneChangeType type;
		std::string sceneName;
		std::string newName;

		SceneChangeRequest(const SceneChangeType& type, const std::string& sceneName, const std::string& newName = "")
			: type(type), sceneName(sceneName), newName(newName) {}
		SceneChangeRequest() { type = NoNeed; sceneName = ""; newName = ""; }
	};

}