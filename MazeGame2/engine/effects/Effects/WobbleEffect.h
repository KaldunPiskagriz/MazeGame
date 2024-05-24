#pragma once
#include "../Effect.h"
#include "../../Logger.hpp"
#include "../../Animatable.h"

class WobbleEffect : public Effect{
	
	float x, y, xAmplitude, yAmplitude, xSpeed, ySpeed;

public:

	WobbleEffect(float xOffset, float yOffset, float xAmplitudeArg, float yAmplitudeArg, float xSpeedArg, float ySpeedArg);
	void ApplyEffect(sf::Sprite& sprite, float sprx, float spry);
	~WobbleEffect();

};