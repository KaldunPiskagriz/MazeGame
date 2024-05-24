#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Logger.hpp"
#include "Singleton.hpp"

class Loader : public Singleton<Loader>{

    Logger* engineLogger = Logger::GetInstance();

public:

	void LoadTexture(std::string file, sf::Texture *texture);
	void LoadSound(std::string file, sf::SoundBuffer *soundBuffer);
    void LoadFont(std::string file, sf::Font* font);

};
