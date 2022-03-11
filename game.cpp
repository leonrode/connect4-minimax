#include "game.h"
#include "board.h"

#include <iostream>
#include <limits>

Game::Game() {
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


		std::cout << "red threats" << activeBoard.countThreeInARows(RED) << " yellow threats " << activeBoard.countThreeInARows(YELLOW) << "\n";
		turn = getNextTurn();

		std::cout << "Computer is placing a piece.\n";
		int computerMove = bestComputerMove(4);


		activeBoard.placePiece(turn, computerMove);

		activeBoard.print();
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
		}


	}

}


int Game::getNextTurn() {
	return turn == RED ? YELLOW : RED;
}

int Game::bestComputerMove(int depth) {
	int bestCol	 = -1;
	int bestEval = std::numeric_limits<int>::max();
	for (int c = 0; c < COLS; c++) {
		Board child = activeBoard;
		bool success = child.placePiece(turn, c);

		if (!success) continue;

		int evaluation = minimax(child, depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(),  turn);
		if (evaluation < bestEval) {
			bestEval = evaluation;
			bestCol = c;
		}
	}

	return bestCol;
}

int Game::evaluateBoard(Board board) {
	int sum = 0;



	const int THREE_WEIGHT = 999999;
	const int TWO_WEIGHT = 9999;

	// evaluation table
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (board.at(r, c) == RED) {
				sum += evaluationTable[r][c];
			} else if (board.at(r, c) == YELLOW) {
				sum -= evaluationTable[r][c];
			}
		}
	}

	// determine threats by finding all three-in-a-rows of the other player
	const int redThreeThreats = board.countThreeInARows(RED);
	const int yellowThreeThreats = board.countThreeInARows(YELLOW);

	const int redTwoThreats = board.countTwoInARows(RED);
	const int yellowTwoThreats = board.countTwoInARows(YELLOW);

	// the more redThreats, the better the position for Red (+)
	sum += redThreeThreats * THREE_WEIGHT;
	sum -= yellowThreeThreats * THREE_WEIGHT;

	sum += redTwoThreats * TWO_WEIGHT;
	sum -= yellowTwoThreats * TWO_WEIGHT;

	// std::cout << sum << "\n";

	// std::cout << "red threats: " << redThreats << "yellowThreats: " << yellowThreats << "\n";

	if (board.checkWin() == RED) {
		// std::cout << "red won\n";

		return 999999;

	}
	else if (board.checkWin() == YELLOW) {
		// std::cout << "YELLOW won\n";
		return -999999;
	}
	else if (board.isBoardFull()) return 0;
	return sum;
}

int Game::minimax(Board board, int depth, int alpha, int beta, const int TURN) {
	// std::cout << "d " << depth << "\n";
	if (depth == 0 || board.isGameOver()) {
		// std::cout << "depth at end" << depth << "game state " << board.isGameOver() <<  "\n";
		// board.print();
		// std::cout << " " <<  evaluateBoard(board) << "\n";
		return evaluateBoard(board);
	}


	if (TURN == RED) {
		int maxEval = std::numeric_limits<int>::min();
		// for each possible move in position
		for (int col = 0; col < COLS; col++) {
			if (board.canPlaceInColumn(col)) {
				// make copy of current board
				Board childBoard = board;
				childBoard.placePiece(TURN, col);

				int evaluation = minimax(childBoard, depth - 1, alpha, beta, YELLOW);
				maxEval = evaluation > maxEval ? evaluation : maxEval;
				alpha = alpha > evaluation ? alpha : evaluation;
				if (beta <= alpha) {
					break;
				}

			}
		}

		return maxEval;
	} else {
		int minEval = std::numeric_limits<int>::max();
		// for each possible move in position
		for (int col = 0; col < COLS; col++) {
			if (board.canPlaceInColumn(col)) {
				// make copy of current board
				Board childBoard = board;
				childBoard.placePiece(TURN, col);

				int evaluation = minimax(childBoard, depth - 1, alpha, beta, RED);
				minEval = evaluation < minEval ? evaluation : minEval;
				beta = beta < evaluation ? beta : evaluation;
				if (beta <= alpha) {
					break;
				}

			}
		}


		return minEval;

	}

	return -1;
}