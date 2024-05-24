#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Logger.hpp"
#include "Singleton.hpp"

class Loader : public Singleton<Loader>{

    class LoadCryptedStream : public sf::InputStream {

        std::string key{ "https://www.youtube.com/watch?v=dQw4w9WgXcQ" };
        int localIndex{ 0 };
        std::string fileName;

    public:

        inline void decryptByte(char* ch);
        std::ifstream source;
        sf::Int64 read(void* data, sf::Int64 size) override;
        sf::Int64 seek(sf::Int64 position) override;
        sf::Int64 tell() override;
        sf::Int64 getSize() override;
        void SetFile(std::string file);
        void LoadSoundFromCrypted(sf::SoundBuffer* buffer);

        LoadCryptedStream(std::string file) : fileName(file) { source.open(file, std::ios::in | std::ios::binary); };
        ~LoadCryptedStream() { source.close(); };

    };

    union SoundLoadingUnion {
        unsigned long long ull{ 0 };
        char bytes[8];
    };

    Logger* engineLogger = Logger::GetInstance();

public:

	void LoadTexture(std::string file, sf::Texture *texture);
	void LoadSound(std::string file, sf::SoundBuffer *soundBuffer);
	void LoadTextureFromEncrypted(std::string file, sf::Texture *texture);
    void LoadSoundFromEncrypted(std::string file, sf::SoundBuffer* soundBuffer);
    void LoadFont(std::string file, sf::Font* font);

};
