#include "Tetris.h"

namespace Tetris {

	Board::Board()
	{
		field = {{0}};
	}

	std::array<std::array<int,10>, 20> & Board::getField() 
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