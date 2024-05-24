#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>
#include "effects/Effect.h"
#include "Animatable.h"

class SimpleGameObject {

public:

	enum SpriteType { AnimatableSprite, OnceAnimatableSprite };

private:

	Animatable *actuallySprite;
	std::function<void()> update;
	std::vector<Effect*> effects;
	SpriteType type{ AnimatableSprite };
	float x, y;

public:

	SimpleGameObject();
	SimpleGameObject(float xArg, float yArg, std::string file, unsigned xSizeArg, unsigned ySizeArg, float speedArg, SpriteType typeArg, std::function<void()> updateArg = 0);
	SimpleGameObject(float xArg, float yArg, sf::Texture* tex, unsigned xSizeArg, unsigned ySizeArg, float speedArg, SpriteType typeArg, std::function<void()> updateArg = 0);
	virtual ~SimpleGameObject();
	void Update();
	void SetUpdateBehaviour(std::function<void()> updateArg);
	void Draw(sf::RenderWindow* window);
	void AddEffect(Effect* effect);
	void DeleteEffectByIndex(unsigned index);
	sf::Vector2f GetPosition() { return sf::Vector2f(x, y); }
	void SetPosition(const sf::Vector2f& pos) { x = pos.x; y = pos.y; }
	void SetPosition(const sf::Vector2i& pos) { x = pos.x; y = pos.y; }
	void SetPosition(const float& xArg, const float& yArg) { x = xArg; y = yArg; }
	sf::Sprite* GetSprite();
	void SetSmooth(bool set) { actuallySprite->GetTexture()->setSmooth(set); }
	void SetAnimationSpeed(const float& speedArg) { actuallySprite->SetAnimationSpeed(speedArg); }
	void SetAnimationFrame(const float& frame) { actuallySprite->SetFrame(frame); }
	void ResetAnimation() { if (type == OnceAnimatableSprite) { static_cast<OnceAnimatable*>(actuallySprite)->ResetAnimation(); } }

};
