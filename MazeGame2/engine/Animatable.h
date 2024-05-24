#pragma once
#include <SFML/Graphics.hpp>
#include "Logger.hpp"
#include <functional>

// Basic class for any Animatable sprite
class Animatable {

protected:

	unsigned x, y, framesNumber;
	sf::Texture texture;
	float speed;
	float currentFrame{0};

public:

	sf::Sprite sprite;

	Animatable(unsigned xArg, unsigned yArg, std::string file, float speedArg);
	Animatable(unsigned xArg, unsigned yArg, sf::Texture* tex, float speedArg);
	Animatable();
	virtual void Update();
	virtual void Draw(sf::RenderWindow *window);
	virtual ~Animatable();
	void SetFrame(float frame);
	void SetAnimationSpeed(const float& speedArg) { speed = speedArg; }
	sf::Texture* GetTexture();

};

// Derived class for every Animatable sprite to play only one time
class OnceAnimatable : public Animatable {

private:

	std::function<void()> action;
	std::function<void()> commonAction = [this] {
		if (currentFrame > framesNumber - 1 || currentFrame < 0) {
			action = [] {};
		}
		currentFrame += speed;
		sprite.setTextureRect(sf::IntRect(0, y * ((int)currentFrame % framesNumber), x, y));
	};

public:

	OnceAnimatable(unsigned xArg, unsigned yArg, std::string file, float speedArg);
	OnceAnimatable(unsigned xArg, unsigned yArg, sf::Texture* tex, float speedArg);
	void ResetAnimation() { action = commonAction; }
	void Update();
	~OnceAnimatable();

};