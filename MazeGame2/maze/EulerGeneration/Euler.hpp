#pragma once
#include <vector>
#include <unordered_map>
#include "../MazeTile.hpp"

class EulerGeneration {
	int y{ 0 };
	int x = { 0 };
	std::vector<int> values;
	int maxValue{ 1 };

	int GetNewValue() {
		maxValue++;
		return maxValue - 1;
	}

	void FillStringValues() {
		for (int i{ 0 }; i < x; i++) {
			if (values[i] == 0) {
				values[i] = GetNewValue();
			}
		}
	}

	void FillStringRightWalls(std::vector<MazeTile>& string) {
		for (int i{ 0 }; i < x - 1; i++) {
			if (values[i] == values[i + 1]) {
				string[i].isRight = true;
			}
			else {
				if (rand() % 2) {
					string[i].isRight = true;
				}
				else {
					values[i + 1] = values[i];
				}
			}
		}
	}

	void FillStringBottomWalls(std::vector<MazeTile>& string) {
		std::unordered_map<int, int> unions;
		for (int i{ 0 }; i < x; i++) {
			unions[values[i]]++;
		}

		int tilesWithBottomWalls{ 0 };
		for (int i{ 0 }; i < x; i++) {

			if (unions[values[i]] > 1) {
				if (unions[values[i]] - tilesWithBottomWalls > 1) {
					int ran = rand() % 2;
					if (ran) {
						string[i].isBottom = true;
						tilesWithBottomWalls++;
					}
				}
			}

		}
	}

	void CopyString(std::vector<MazeTile>& string1, std::vector<MazeTile>& string2) {
		for (int i{ 0 }; i < x; i++) {
			string2[i] = string1[i];
		}
	}

	void PrepareCopiedString(std::vector<MazeTile>& string) {
		for (int i{ 0 }; i < x; i++) {
			string[i].isRight = false;
			if (string[i].isBottom) {
				string[i].isBottom = false;
				values[i] = 0;
			}
		}
	}

	void PrepareLastString(std::vector<MazeTile>& string) {
		for (int i{ 0 }; i < x - 1; i++) {
			if (values[i] != values[i + 1]) {
				values[i + 1] = values[i];
				string[i].isRight = false;
			}
		}
	}

public:

	void Generate(std::vector<std::vector<MazeTile>>& map, int seed) {
		srand(seed);
		maxValue = 1;
		y = map.size();
		x = map[0].size();
		values.resize(x);

		for (int i{ 0 }; i < y; i++) {
			FillStringValues();
			FillStringRightWalls(map[i]);
			FillStringBottomWalls(map[i]);
			if (i < y - 1) {
				CopyString(map[i], map[i + 1]);
				PrepareCopiedString(map[i + 1]);
			}
			else {
				PrepareLastString(map[i]);
			}
		}
	}

};