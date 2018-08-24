#include "Tetris.h"

namespace Tetris {

	Board::Board(int M, int N):M(M), N(N), field(M)
	{
		for (int i = 0; i < field.size(); i++) {
			field[i].resize(N);
		}
		for (int i = 0; i < field.size(); i++) {
			for (int j = 0; j < field[0].size(); j++) {
				field[i][j] = 0;
			}
		}
	}

	std::vector<std::vector<int>> & Board::getField() 
	{
		return field;
	}
	
	int Board::getLines()
	{
		return M;
	}
	int Board::getCollumns()
	{
		return N;
	}

	////////////////////////////////////////////////////

	Piece::Piece(int _type, int _color):type(_type), color(_color){}

	std::array<int,4> Piece::getFigure()
	{
		return figures.at(type);
	}

	int Piece::getType() 
	{
		return type;
	}

	int Piece::getColor()
	{
		return color;
	}
}