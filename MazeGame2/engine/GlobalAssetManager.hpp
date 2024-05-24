#pragma once
#include <unordered_map>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Singleton.hpp"
#include "Loader.hpp"
#include "Logger.hpp"

class GlobalAssetManager : public Singleton<GlobalAssetManager> {

	std::unordered_map<std::string, sf::Texture*> textures;
	std::mutex mutex;

public:

	void AddTexture(std::string name, sf::Texture* tex) { std::lock_guard guard(mutex); textures[name] = tex; }

	void AddTexture(std::string name, std::string filename) { 
		Loader* loader = Loader::GetInstance();
		std::lock_guard guard(mutex);
		loader->LoadTexture(filename, textures[name]);
	}

	sf::Texture* GetTexture(std::string name) { 
		try {
			return textures.at(name);
		}
		catch (const std::out_of_range& e) {
			Logger* logger = Logger::GetInstance();
			logger->PrintError("[ GlobalAssetManager ]: Cannot find texture with name \"" + name + "\"");
		}
		return nullptr;
	}

	void DeleteTexture(std::string name) { std::lock_guard guard(mutex); textures.erase(name); }

};