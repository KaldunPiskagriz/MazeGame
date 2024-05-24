#include "Loader.hpp"

//Loader methods:
void Loader::LoadTexture(std::string file, sf::Texture* texture) {
	if (texture->loadFromFile(file)) {
        engineLogger->PrintMessage("Successfully loaded sprite from file: " + file);
		return;
	}
    engineLogger->PrintError("Failed to load sprite from file: " + file);
}

void Loader::LoadSound(std::string file, sf::SoundBuffer* soundBuffer) {
	if (soundBuffer->loadFromFile(file)) {
        engineLogger->PrintMessage("Successfully loaded sound from file: " + file);
		return;
	}
    engineLogger->PrintError("Failed to load sound from file: " + file);
}

void Loader::LoadFont(std::string file, sf::Font* font) {
    font->loadFromFile(file);
}