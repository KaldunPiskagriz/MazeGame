#include "Animatable.h"
#include "Loader.hpp"

// Animatable realisation

Animatable::Animatable(unsigned xArg, unsigned yArg, std::string file, float speedArg)
	: x(xArg), y(yArg), speed(speedArg){
	
	Loader* engineLoader = Loader::GetInstance();
	engineLoader->LoadTexture(file, &texture);
	framesNumber = texture.getSize().y / yArg;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, x, y));
}

Animatable::Animatable(unsigned xArg, unsigned yArg, sf::Texture* tex, float speedArg) 
	: x(xArg), y(yArg), speed(speedArg) {

	framesNumber = tex->getSize().y / yArg;
	sprite.setTexture(*tex);
	sprite.setTextureRect(sf::IntRect(0, 0, x, y));
}

Animatable::Animatable()
	:x(0), y(0), speed(0), framesNumber(1){

}

void Animatable::Update() {
	currentFrame += speed;
	sprite.setTextureRect(sf::IntRect(0, y * ((int)currentFrame % framesNumber), x, y));
}

void Animatable::Draw(sf::RenderWindow* window) {

	window->draw(sprite);

}

void Animatable::SetFrame(float frame) {
	currentFrame = frame;
}

sf::Texture* Animatable::GetTexture() {
	return const_cast<sf::Texture*>(sprite.getTexture());
}

Animatable::~Animatable() {

}


// Once Animatable realisation

OnceAnimatable::OnceAnimatable(unsigned xArg, unsigned yArg, std::string file, float speedArg)
	: Animatable(xArg, yArg, file, speedArg) {

	action = commonAction;

}

OnceAnimatable::OnceAnimatable(unsigned xArg, unsigned yArg, sf::Texture* tex, float speedArg) 
	: Animatable(xArg, yArg, tex, speedArg) {

	action = commonAction;
}

void OnceAnimatable::Update() {
	action();
}

OnceAnimatable::~OnceAnimatable() {

}
