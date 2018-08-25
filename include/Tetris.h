#pragma once
#include <array>
#include <vector>

namespace Tetris {
	/**
	 * @brief     Coordinates of a point in the Tetris board.
	 */
	struct Point {
		int x,y;
	};

	/**
	 * @brief      Class for the Tetris board.
	 */
	class Board {

	public:
		/**
		 * @brief      Constructs the board
		 *
		 * @param[in]  M     the number of lines
		 * @param[in]  N     the number of collumns
		 */
		Board();
		/**
		 * @brief      Gets the tetris field (as reference)
		 *
		 * @return     The field (2-dimensional vector of int).
		 */
		std::array<std::array<int, 10>,20> & getField();

		/**
		 * @brief      Gets the number of lines
		 *
		 * @return     The number of lines.
		 */
		int getLines();

		/**
		 * @brief      Gets the number of collumns.
		 *
		 * @return     The number of collumns.
		 */
		int getCollumns();
		
	private:
		int M = 20;
		int N = 10;
		std::array<std::array<int,10>,20> field;
	};

	/**
	 * @brief      Class for the tetris pieces.
	 */
	class Piece {
	public:
		/**
		 * @brief      Constructs the Tetris piece
		 *
		 * @param[in]  type   The type of the piece
		 * @param[in]  color  The color of the piece
		 */
		Piece(int type, int color);

		/**
		 * @brief      Gets the figure of the piece.
		 *
		 * @return     The figure of the piece (as an integer std::array).
		 * 			   As this returns a c++11 array, we recommend usage of
		 * 			   .at() instead of [], in order to obtain bound safety.
		 */
		std::array<int, 4> getFigure();

		/**
		 * @brief      Gets the color of the piece.
		 *
		 * @return     The color.
		 */
		int getColor();

		/**
		 * @brief      Gets the type of the piece.
		 *
		 * @return     The type.
		 */
		int getType();
	private:
		int type;
		int color;
		std::array<std::array<int,4>, 7> figures = 
		{{
			{1,3,5,7}, // I
			{2,4,5,7}, // Z
			{3,5,4,6}, // S
			{3,5,4,7}, // T
			{2,3,5,7}, // L
			{3,5,7,6}, // J
			{2,3,4,5} // O
		}};

	};	
}
