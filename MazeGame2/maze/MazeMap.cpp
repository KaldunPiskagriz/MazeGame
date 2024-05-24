#include "MazeMap.hpp"

void MazeMap::DrawRect(sf::RectangleShape rect, sf::RenderWindow* window, short dir) {
	switch (dir) {
	case 0:
		rect.setRotation(0);
		break;
	case 1:
		rect.setRotation(90);
		break;
	case 2:
		rect.setRotation(180);
		break;
	case 3:
		rect.setRotation(-90);
		break;
	}
	window->draw(rect);
}

void MazeMap::Init(int size, int windowHeight, int windowWidth) {
	map = std::vector<std::vector<MazeTile>>(size, std::vector<MazeTile>(size));
	tileSideLenght = windowHeight * 0.8f / map.size();
	rect.setSize(sf::Vector2f(tileSideLenght + borderThickness, borderThickness));
	rect.setFillColor(sf::Color::White);
	rect.setOrigin(rect.getLocalBounds().width / 2.0f, borderThickness / 2.0f + tileSideLenght / 2.0f);

	leftCorner = windowWidth / 2.0f - windowHeight * 0.4f ;
	upCorner = windowHeight * 0.1f + 16.0f;
}

void MazeMap::GenerateMap(const GenerationMethod& method, int seed) {
	for (int i{ 0 }; i < map.size(); i++) {
		for (int j{ 0 }; j < map.size(); j++) {
			map[i][j].isBottom = false;
			map[i][j].isRight = false;
		}
	}
	switch (method) {


	case Euler:
		EulerGeneration generator;
		generator.Generate(map, seed);
		break;

	}

	int where{ rand() % 4 };
	switch (where) {
	case 0:
		start = sf::Vector2i(0, 0);
		finish = sf::Vector2i(map.size() - 1, map.size() - 1);
		break;
	case 1:
		start = sf::Vector2i(map.size() - 1, 0);
		finish = sf::Vector2i(0, map.size() - 1);
		break;
	case 2:
		start = sf::Vector2i(0, map.size() - 1);
		finish = sf::Vector2i(map.size() - 1, 0);
		break;
	case 3:
		start = sf::Vector2i(map.size() - 1, map.size() - 1);
		finish = sf::Vector2i(0, 0);
		break;
	}
}

void MazeMap::DrawMap(sf::RenderWindow* window) {
	
	for (int i{ 0 }; i < map.size(); i++) {
		for (int j{ 0 }; j < map[i].size(); j++) {

			rect.setPosition(MapCoords(j, i));

			if (map[i][j].isRight){ DrawRect(rect, window, 1); }
			if (map[i][j].isBottom) { DrawRect(rect, window, 2); }

		}
	}

	for (int i{ 0 }; i < map.size(); i++) {
		rect.setPosition(MapCoords(i, 0));
		DrawRect(rect, window, 0);
	}

	for (int i{ 0 }; i < map.size(); i++) {
		rect.setPosition(MapCoords(i, map.size()-1));
		DrawRect(rect, window, 2);
	}

	for (int i{ 0 }; i < map.size(); i++) {
		rect.setPosition(MapCoords(0, i));
		DrawRect(rect, window, 3);
	}

	for (int i{ 0 }; i < map.size(); i++) {
		rect.setPosition(MapCoords(map.size()-1, i));
		DrawRect(rect, window, 1);
	}

}

sf::Vector2f MazeMap::MapCoords(const float& x, const float& y) {
	return sf::Vector2f(leftCorner + tileSideLenght / 2 + tileSideLenght * x, upCorner + tileSideLenght / 2 + tileSideLenght * y);
}

sf::Vector2f MazeMap::MapCoords(sf::Vector2f coords){
	return MapCoords(coords.x, coords.y);
}

bool MazeMap::CheckPassage(const sf::Vector2f& start, const int& dedstination) {
	switch (dedstination) {
	case 0:
		if (start.y > 0 && !map[start.y - 1][start.x].isBottom) { return true; }
		else { return false; }
		break;
	case 1:
		if (start.x < map.size() - 1 && !map[start.y][start.x].isRight) { return true; }
		else { return false; }
		break;
	case 2:
		if (start.y < map.size() - 1 && !map[start.y][start.x].isBottom) { return true; }
		else { return false; }
		break;
	case 3:
		if (start.x > 0 && !map[start.y][start.x-1].isRight) { return true; }
		else { return false; }
		break;
	}
}


