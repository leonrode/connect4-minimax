#include "game.h"
#include "board.h"
#include <iostream>

Game::Game() {
	// activeBoard.placePiece(YELLOW, 4);
	turn = RED;

	playGame();
	
}


void Game::playGame() {


	bool won = false;
	while (!won) {
		// get user input

		int playerCol;
		std::cout << "Enter a column (0-6): ";
		std::cin >> playerCol;
		std::cout << "\n";


		bool success = activeBoard.placePiece(turn, playerCol);
		while (!success) {
			std::cout << "Column is full. Enter a column (0-6): ";
			std::cin >> playerCol;
			std::cout << "\n";
			success = activeBoard.placePiece(turn, playerCol);
		}

		if (activeBoard.isBoardFull()) {
			std::cout << "Board is full! Tie!\n";
			break;
		}

		std::cout << "Computer is placing a piece.\n";
		int computerMove = bestComputerMove();

		turn = getNextTurn();

		activeBoard.placePiece(turn, computerMove);

		if (activeBoard.checkWin() == RED) {
			std::cout << "Red player wins!\n";
			won = true;
		} else if (activeBoard.checkWin() == YELLOW) {
			std::cout << "Yellow computer wins!\n";
			won = true;
		
		} else if (activeBoard.isBoardFull()) {
			std::cout << "Board is full! Tie!\n";
			won = true;
		} else {
			// swap turn

			turn = getNextTurn();
			activeBoard.print();
		}


	}

}


int Game::getNextTurn() {
	return turn == RED ? YELLOW : RED;
}

int Game::bestComputerMove() {
	int bestCol	 = -1;
	int bestEval = 1000000;
	for (int c = 0; c < COLS; c++) {
		Board child = activeBoard;
		bool success = child.placePiece(getNextTurn(), c);

		if (!success) continue;

		int evaluation = minimax(child, 4, getNextTurn());
		if (evaluation < bestEval) {
			bestEval = evaluation;
			bestCol = c;
		}
	}

	return bestCol;
}

int Game::evaluateBoard(Board board) {
	int sum = 0;

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (board.at(r, c) == RED) {
				sum += evaluationTable[r][c];
			} else if (board.at(r, c) == YELLOW) {
				sum -= evaluationTable[r][c];
			}
		}
	}

	return sum;
}

int Game::minimax(Board board, const int depth, const int TURN) {

	if (depth == 0 || board.isGameOver()) { // TODO depth == 0 or game OVER

		return evaluateBoard(board);
	}


	if (TURN == RED) {
		int maxEval = -100000;
		// for each possible move in position
		for (int col = 0; col < COLS; col++) {
			if (board.canPlaceInColumn(col)) {
				// make copy of current board
				Board childBoard = board;
				childBoard.placePiece(TURN, col);


				int evaluation = minimax(childBoard, depth - 1, YELLOW); 
				maxEval = evaluation > maxEval ? evaluation : maxEval;
			}
		}

		return maxEval;
	} else {
		int minEval = 100000;
		// for each possible move in position
		for (int col = 0; col < COLS; col++) {
			if (board.canPlaceInColumn(col)) {
				// make copy of current board
				Board childBoard = board;
				childBoard.placePiece(TURN, col);

				int evaluation = minimax(childBoard, depth - 1, RED); 
				minEval = evaluation < minEval ? evaluation : minEval;

			}
		}


		return minEval;

	}

	return -1;
}	