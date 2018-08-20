#pragma once
#include <vector>

namespace Tetris {
	struct Point {
		int x,y;
	};
	class Board {

	public:
		Board(int M, int N);
		std::vector<std::vector<int>> & getField();
		int getLines();
		int getCollumns();

	private:
		int M, N;
		std::vector<std::vector<int>> field;
	};

	class Piece {
	public:
		Piece(int type, int color);
		std::vector<int> getFigure();
		int getColor();
		int getType();
	private:
		int type;
		int color;
		std::vector<std::vector<int>> figures = 
		{
			{1,3,5,7}, // I
			{2,4,5,7}, // Z
			{3,5,4,6}, // S
			{3,5,4,7}, // T
			{2,3,5,7}, // L
			{3,5,7,6}, // J
			{2,3,4,5}, // O
		};

	};	
}
