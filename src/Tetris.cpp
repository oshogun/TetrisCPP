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

	std::vector<std::vector<int>> Board::getField() 
	{
		return field;
	}
	
}