#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Loader.hpp"

class SoundPad {

	struct BasicSound {
		sf::Sound sound;
		sf::SoundBuffer soundBuffer;
	};

	std::unordered_map<std::string, BasicSound> sounds;

public:

	SoundPad();
	void LoadSound(std::string file, std::string name);
	void PlaySnd(std::string name);

};