#include "GameScene.hpp"

void GameScene::MapGeneratedCallback() {
	isMapClosing = false;
	currentState = openingMap;
	elevatorEnter.GetSprite()->setScale(mazeMap.GetTileSideLenght() / 32, mazeMap.GetTileSideLenght() / 32);
	elevatorExit.GetSprite()->setScale(mazeMap.GetTileSideLenght() / 32, mazeMap.GetTileSideLenght() / 32);
	elevatorEnter.GetSprite()->setOrigin(elevatorEnter.GetSprite()->getLocalBounds().width / 2.0f, elevatorEnter.GetSprite()->getLocalBounds().height / 2.0f);
	elevatorExit.GetSprite()->setOrigin(elevatorExit.GetSprite()->getLocalBounds().width / 2.0f, elevatorExit.GetSprite()->getLocalBounds().height / 2.0f);
	elevatorEnter.SetPosition(mazeMap.MapCoords(mazeMap.GetStartPos()));
	elevatorExit.SetPosition(mazeMap.MapCoords(mazeMap.GetFinishPos()));

	elevatorEnter.ResetAnimation();
	elevatorEnter.SetAnimationSpeed(-0.125f);

	balbes.SetPosition(elevatorEnter.GetPosition());
	balbesPos = mazeMap.GetStartPos();
	balbes.GetSprite()->setScale(mazeMap.GetTileSideLenght() / (32 + 500), mazeMap.GetTileSideLenght() / (32 + 500));
	balbes.GetSprite()->setOrigin(balbes.GetSprite()->getLocalBounds().width / 2.0f, balbes.GetSprite()->getLocalBounds().height / 2.0f);
}

void GameScene::MoveBalbes(const sf::Event& event) {
	if (!isActive) { return; }
	if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
		if (mazeMap.CheckPassage(balbesPos, 0)) {
			destinationPos.y = balbesPos.y - 1;
			isActive = false;
		}
	}
	if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
		if (mazeMap.CheckPassage(balbesPos, 1)) {
			destinationPos.x = balbesPos.x + 1;
			isActive = false;
		}
		balbes.GetSprite()->setScale(abs(balbes.GetSprite()->getScale().x), balbes.GetSprite()->getScale().y);
	}
	if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
		if (mazeMap.CheckPassage(balbesPos, 2)) {
			destinationPos.y = balbesPos.y + 1;
			isActive = false;
		}
	}
	if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
		if (mazeMap.CheckPassage(balbesPos, 3)) {
			destinationPos.x = balbesPos.x - 1;
			isActive = false;
		}
		balbes.GetSprite()->setScale(abs(balbes.GetSprite()->getScale().x) * -1, balbes.GetSprite()->getScale().y);
	}
}