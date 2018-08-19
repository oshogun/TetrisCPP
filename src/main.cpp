#include "Tetris.h"
#include <iostream>

int main()
{
	Tetris::Board board(20,10);
	std::vector<std::vector<int>> b = board.getField();
	for(int i = 0; i < 20; i++) {
		std::cout << "{ ";
		for (int j = 0; j < 10; j++) {
			std::cout << b[i][j] << " ";
		}
		std::cout << "}\n";
	}
}