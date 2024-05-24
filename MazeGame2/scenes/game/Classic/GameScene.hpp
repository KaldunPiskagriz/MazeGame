#pragma once
#include <SFML/Graphics.hpp>
#include "../../SceneWithFade.hpp"
#include "../../../maze/MazeMap.hpp"
#include "../../../engine/Engine.hpp"
#include <optional>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <random>

extern unsigned windowWidth;
extern unsigned windowHeight;

class GameScene : public SceneWithFade {

public:
	enum currentStateEnum { fading, closingMap, generating, openingMap, gaming };

private:
	MazeMap mazeMap;
	unsigned currentLevel{ 1 };
	bool isActive{ false };
	currentStateEnum currentState{fading};
	sf::RectangleShape mazeRect{ sf::Vector2f(windowHeight * 0.4, windowHeight * 0.8) };
	std::optional<bool> isMapClosing;
	MultithreadingSystem::ThreadPool* threadpool;
	sf::Vector2f balbesPos{-1, -1};
	SimpleGameObject elevatorEnter{ -100, -100, "assets/elevator.png", 32, 32, 0, SimpleGameObject::OnceAnimatableSprite, [] {} };
	SimpleGameObject elevatorExit{ -100, -100, "assets/elevator.png", 32, 32, 0, SimpleGameObject::OnceAnimatableSprite, [] {} };
	SimpleGameObject balbes{ -1000, -1000, "assets/balbes.png", 388, 397, 0, SimpleGameObject::OnceAnimatableSprite, [] {} };
	sf::Vector2f destinationPos{-1, -1};
	int animationFrame{ 0 };
	int currentSize{ 5 };
	TextsDB* texts;

	void MapGeneratedCallback();
	void MoveBalbes(const sf::Event& event);

protected:

	void SceneFadedInCallback() {
		currentState = generating;
	}

public:

	GameScene() : SceneWithFade() {
		mazeRect.setFillColor(sf::Color::White);
		texts = TextsDB::GetInstance();

		GUI.CreateLabel("level", 0.5, 0.03, texts->GetText("level") + L"1" + L"/5", "base", 0.1);

		threadpool = MultithreadingSystem::ThreadPool::GetInstance();

		elevatorEnter.SetAnimationFrame(6);

		EventHandler::GetInstance()->RegisterEventListener(std::bind(&GameScene::MoveBalbes, this, std::placeholders::_1), sf::Event::KeyPressed);
	}

	void Tick() {

		if (currentState == generating && !threadpool->GetStatus()) {
			threadpool->AddTask([this] { 
				unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
				std::default_random_engine generator(seed);
				std::uniform_real_distribution<double> distributionDouble(1.0, 1000000.0); 
				mazeMap.Init(currentSize, windowHeight, windowWidth); mazeMap.GenerateMap(MazeMap::Euler, distributionDouble(generator)); MapGeneratedCallback();
			}, MultithreadingSystem::other, "generate map");
		}

		if (currentState == openingMap && !mazeRect.getSize().x) {
			currentState = gaming;
			elevatorEnter.SetUpdateBehaviour([this] {
				float alpha = elevatorEnter.GetSprite()->getColor().a;
				alpha = std::clamp(alpha - 5.0f, 0.0f, 255.0f);
				sf::Color color;
				color = elevatorEnter.GetSprite()->getColor();
				color.a = alpha;
				elevatorEnter.GetSprite()->setColor(color);
				if (alpha == 0) {
					color.a = 255;
					elevatorEnter.GetSprite()->setColor(color);
					elevatorEnter.SetPosition(-100, -100);
					elevatorEnter.SetUpdateBehaviour([] {});
				}
			});

			balbes.SetUpdateBehaviour([this] { 
				if (destinationPos.x != -1) {
					if (animationFrame < 10) {
						balbesPos.x += 0.1 * ((destinationPos.x - balbesPos.x) / abs(destinationPos.x - balbesPos.x));
						animationFrame++;
					}
					if (animationFrame == 10) {
						isActive = true;
						balbesPos.x = static_cast<int>(destinationPos.x);
						destinationPos.x = -1;
						animationFrame = 0;
					}
				}
				if (destinationPos.y != -1) {
					if(animationFrame < 10) {
						balbesPos.y += 0.1 * ((destinationPos.y - balbesPos.y) / abs(destinationPos.y - balbesPos.y));
						animationFrame++;
					}
					if (animationFrame == 10) {
						isActive = true;
						balbesPos.y = static_cast<int>(destinationPos.y);
						destinationPos.y = -1;
						animationFrame = 0;
					}
				}
				balbes.SetPosition(mazeMap.MapCoords(balbesPos)); 
			});

			isActive = true;
		}

		if (currentState == closingMap && mazeRect.getLocalBounds().width == windowHeight * 0.4) {
			currentLevel++;
			if (currentLevel == 6) {
				GoTo("victory");
				currentState = fading;
			}
			else {
				currentState = generating;
				isMapClosing.reset();
				static_cast<Label*>(GUI.GetElementByName("level"))->labelText.setString(texts->GetText("level") + std::to_wstring(currentLevel) + L"/5");
				elevatorExit.SetAnimationFrame(0);
				elevatorExit.SetAnimationSpeed(0);
				currentSize++;
			}
		}

		if (isMapClosing.has_value()) {
			mazeRect.setSize(sf::Vector2f(std::clamp((isMapClosing.value() ? mazeRect.getSize().x + 5 : mazeRect.getSize().x - 5), 0.0f, windowHeight * 0.4f), mazeRect.getSize().y));
		}

		elevatorEnter.Update();
		elevatorExit.Update();
		balbes.Update();

		if (balbesPos == mazeMap.GetFinishPos()) {
			isActive = false;
			isMapClosing = true;
			elevatorExit.ResetAnimation();
			elevatorExit.SetAnimationSpeed(0.125f);
			currentState = closingMap;
			balbesPos = sf::Vector2f{ -100, -100 };
		}

		InternalTick();
	}

	void Draw(sf::RenderWindow* window) {
		mazeMap.DrawMap(window);

		balbes.Draw(window);

		elevatorEnter.Draw(window);
		elevatorExit.Draw(window);

		mazeRect.setOrigin(0, 0);
		mazeRect.setPosition(windowWidth / 2.0f - windowHeight * 0.4f, windowHeight * 0.1 + 16);
		window->draw(mazeRect);
		mazeRect.setOrigin(mazeRect.getSize().x, 0);
		mazeRect.setPosition(windowWidth / 2.0f + windowHeight * 0.4f, windowHeight * 0.1 + 16);
		window->draw(mazeRect);

		GUI.DrawGUI(window);
		InternalDraw(window);
	}

};