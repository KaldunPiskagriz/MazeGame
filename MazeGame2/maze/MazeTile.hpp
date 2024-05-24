#pragma once

struct MazeTile {
	bool isRight{};
	bool isBottom{};
	MazeTile() { isRight = isBottom = false; }
	MazeTile(bool right, bool bottom) : isRight(right), isBottom(bottom) {}
};