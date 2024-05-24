#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "MazeTile.hpp"
#include "EulerGeneration/Euler.hpp"

class MazeMap {

	float borderThickness{ 5 };
	float tileSideLenght{ 32 };
	sf::RectangleShape rect;

	sf::Vector2i start{ 0, 0 };
	sf::Vector2i finish{ 0, 0 };

	float leftCorner{ 0 };
	float upCorner{ 0 };

	void DrawRect(sf::RectangleShape rect, sf::RenderWindow* window, short dir);

public:

	std::vector<std::vector<MazeTile>> map;
	enum GenerationMethod { Euler };

	void Init(int size, int windowHeight, int windowWidth);
	void GenerateMap(const GenerationMethod& method, int seed);
	void DrawMap(sf::RenderWindow* window);
	sf::Vector2f GetStartPos() { return sf::Vector2f(start.x, start.y); }
	sf::Vector2f GetFinishPos() { return sf::Vector2f(finish.x, finish.y); }
	float GetTileSideLenght() { return tileSideLenght; }
	sf::Vector2f MapCoords(const float& x, const float& y);
	sf::Vector2f MapCoords(sf::Vector2f coords);
	bool CheckPassage(const sf::Vector2f& start, const int& dedstination);

};