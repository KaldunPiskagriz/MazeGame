#include "SimpleGameObject.h"

SimpleGameObject::SimpleGameObject() {
	x = 0;
	y = 0;
	actuallySprite = new Animatable;
	update = [] {};
}

SimpleGameObject::SimpleGameObject(float xArg, float yArg, std::string file, unsigned xSizeArg, unsigned ySizeArg, float speedArg, SpriteType typeArg, std::function<void()> updateArg)
	: x(xArg), y(yArg) {

	if (typeArg == AnimatableSprite) {
		actuallySprite = new Animatable(xSizeArg, ySizeArg, file, speedArg);
	}
	else if (typeArg == OnceAnimatableSprite) {
		actuallySprite = new OnceAnimatable(xSizeArg, ySizeArg, file, speedArg);
	}

	actuallySprite->sprite.setPosition(xArg, yArg);
	if (!updateArg && type == OnceAnimatableSprite) {
		static_cast<OnceAnimatable*>(actuallySprite)->ResetAnimation();
		return;
	}
	update = updateArg;
}

SimpleGameObject::SimpleGameObject(float xArg, float yArg, sf::Texture* tex, unsigned xSizeArg, unsigned ySizeArg, float speedArg, SpriteType typeArg, std::function<void()> updateArg) 
	: x(xArg), y(yArg) {

	if (typeArg == AnimatableSprite) {
		actuallySprite = new Animatable(xSizeArg, ySizeArg, tex, speedArg);
	}
	else if (typeArg == OnceAnimatableSprite) {
		actuallySprite = new OnceAnimatable(xSizeArg, ySizeArg, tex, speedArg);
	}

	actuallySprite->sprite.setPosition(xArg, yArg);
	if (!updateArg && type == OnceAnimatableSprite) {
		static_cast<OnceAnimatable*>(actuallySprite)->ResetAnimation();
		return;
	}
	update = updateArg;

}

void SimpleGameObject::Draw(sf::RenderWindow *window) {
	for (int i = 0; i < effects.size(); i++) {
		effects[i]->ApplyEffect(actuallySprite->sprite, x, y);
	}
	window->draw(actuallySprite->sprite);
}

void SimpleGameObject::Update()	{
	update();
	actuallySprite->Update();
	actuallySprite->sprite.setPosition(x, y);
}

void SimpleGameObject::SetUpdateBehaviour(std::function<void()> updateArg)	{
	update = updateArg;
}

void SimpleGameObject::AddEffect(Effect* effect) {
	effects.push_back(effect);
}

void SimpleGameObject::DeleteEffectByIndex(unsigned index) {
	effects.erase(effects.begin() + index);
}

sf::Sprite* SimpleGameObject::GetSprite() {
	return &(actuallySprite->sprite);
}

SimpleGameObject::~SimpleGameObject() {
	delete actuallySprite;
	for (int i = 0; i < effects.size(); i++) {
		delete effects[i];
	}
}