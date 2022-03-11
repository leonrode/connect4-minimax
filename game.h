#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game {
	private:
		int evaluationTable[6][7] = {{3, 4, 5, 7, 5, 4, 3},
									{4, 6, 8, 10, 8, 6, 4},
									{5, 8, 11, 13, 11, 8, 5},
									{5, 8, 11, 13, 11, 8, 5},
									{4, 6, 8, 10, 8, 6, 4},
									{3, 4, 5, 7, 5, 4, 3}};

		int turn;
		int getNextTurn();

	public:
		Board activeBoard;

		const int RED = 2;
		const int YELLOW = 1;

		const int ROWS = 6;
		const int COLS = 7;

		Game();
		int bestComputerMove(int depth);
		int evaluateBoard(Board board);

		void playGame();
		/*
			Returns evaluation of the best position for
			the initial turn
		*/
		int minimax(Board board, const int depth, int alpha, int beta, const int TURN);
};

#endif
