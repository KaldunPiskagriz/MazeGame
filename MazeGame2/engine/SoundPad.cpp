#include "SoundPad.h"

// SoundPad methods realisation

SoundPad::SoundPad() {
	sounds.clear();
}

void SoundPad::LoadSound(std::string file, std::string name) {
	Loader* engineLoader = Loader::GetInstance();
	file.ends_with(".enc") ? engineLoader->LoadSoundFromEncrypted(file, &(sounds[name].soundBuffer)) : engineLoader->LoadSound(file, &(sounds[name].soundBuffer));
	sounds[name].sound.setBuffer(sounds[name].soundBuffer);
}

void SoundPad::PlaySnd(std::string name) {
	sounds[name].sound.play();
}