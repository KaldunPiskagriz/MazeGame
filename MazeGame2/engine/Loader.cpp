#include "Loader.hpp"

//LoadCryptedStream methods:

void Loader::LoadCryptedStream::decryptByte(char* ch) {
    *ch = *ch ^ key[localIndex];
    localIndex++;
    if (localIndex == key.length()) { localIndex = 0; };
}

sf::Int64 Loader::LoadCryptedStream::read(void* data, sf::Int64 size) {
    char* castedData = static_cast<char*>(data);
    char* secondCastedData = castedData;
    source.read(secondCastedData, size);

    for (int i = 0; i < size; i++) {
        decryptByte(castedData);
        castedData++;
    }

    return source.gcount();
}

sf::Int64 Loader::LoadCryptedStream::seek(sf::Int64 position) {
    source.seekg(position);
    localIndex = position % key.length();
    return source.tellg();
}

sf::Int64 Loader::LoadCryptedStream::tell() {
    return source.tellg();
}

sf::Int64 Loader::LoadCryptedStream::getSize() {
    std::streampos currentPosition = source.tellg();
    source.seekg(0, std::ios::end);
    std::streampos size = source.tellg();
    source.seekg(currentPosition);
    return size;
}

void Loader::LoadCryptedStream::SetFile(std::string file) {
    source.close();
    source.open(file, std::ios::binary);
    if (!source) {
        Logger* engineLogger = Logger::GetInstance();
        engineLogger->PrintError("Failed to open file: " + file);
    }
    fileName = file;
}

void Loader::LoadCryptedStream::LoadSoundFromCrypted(sf::SoundBuffer* buffer) {
    unsigned int channelCount{ 0 };
    unsigned long long sampleCount{ 0 };
    unsigned int sampleRate{ 0 };

    SoundLoadingUnion tempLoader;

    source.read(tempLoader.bytes, 4); 
    for (int i{ 0 }; i < 4; i++) { decryptByte(&(tempLoader.bytes[i])); } 
    channelCount = tempLoader.ull;

    source.read(tempLoader.bytes, 8); 
    for (int i{ 0 }; i < 8; i++) { decryptByte(&(tempLoader.bytes[i])); } 
    sampleCount = tempLoader.ull;

    source.read(tempLoader.bytes, 4); 
    for (int i{ 0 }; i < 4; i++) { decryptByte(&(tempLoader.bytes[i])); } 
    sampleRate = tempLoader.ull;

    std::vector<sf::Int16> samples{ 0 };
    sf::Int16 sample{ 0 };
    while (source) {
        source.read(tempLoader.bytes, 2);
        decryptByte(&(tempLoader.bytes[0])); decryptByte(&(tempLoader.bytes[1]));
        sample = tempLoader.ull;
        samples.emplace_back(sample);
    }

    Logger* engineLogger = Logger::GetInstance();
    if ((buffer->loadFromSamples(&(samples[0]), sampleCount, channelCount, sampleRate))) {
        engineLogger->PrintMessage("Successfully loaded sound from encrypted file: " + fileName);
        return;
    }
    engineLogger->PrintError("Failed to load sound from encrypted file: " + fileName);
}

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

void Loader::LoadTextureFromEncrypted(std::string file, sf::Texture* texture) {
    LoadCryptedStream stream(file);
    if (texture->loadFromStream(stream)) {
        engineLogger->PrintMessage("Successfully loaded texture from encrypted file: " + file);
        return;
    }
    engineLogger->PrintError("Failed to load texture from encrypted file: " + file);
}

void Loader::LoadSoundFromEncrypted(std::string file, sf::SoundBuffer* soundBuffer) {
    LoadCryptedStream stream(file);
    stream.LoadSoundFromCrypted(soundBuffer);
}

void Loader::LoadFont(std::string file, sf::Font* font) {
    font->loadFromFile(file);
}