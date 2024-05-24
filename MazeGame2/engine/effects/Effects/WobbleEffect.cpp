#include "WobbleEffect.h"

WobbleEffect::WobbleEffect(float xOffset, float yOffset, float xAmplitudeArg, float yAmplitudeArg, float xSpeedArg, float ySpeedArg) 
	: x(xOffset * 3.14 / 180), y(yOffset * 3.14 / 180), xAmplitude(xAmplitudeArg), yAmplitude(yAmplitudeArg), xSpeed(xSpeedArg * 3.14 / 180), ySpeed(ySpeedArg * 3.14 / 180){
}

void WobbleEffect::ApplyEffect(sf::Sprite& sprite, float sprx, float spry) {
	sprite.setPosition(sf::Vector2f(static_cast<int>(sprx + sin(x) * xAmplitude), static_cast<int>(spry + sin(y) * yAmplitude)));
	x += xSpeed;
	y += ySpeed;
}

WobbleEffect::~WobbleEffect() {
	Logger* engineLogger = Logger::GetInstance();
	engineLogger->PrintMessage("wobbleEffect object destroyed");
}