#include "game.h"
#include <iostream>

Game::Game() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			board[r][c] = 0;
		}
	}
}

void Game::print() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			std::cout << board[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

bool Game::placePiece(bool white, int col) {
	if (isColFull(col)) return false;

	int r = 0;
	while (r < ROWS - 1 && board[r + 1][col] == 0) {
		r++;
	}

	board[r][col] = white ? 2 : 1;

	return true;
}

bool Game::isColFull(int col) {
	return board[0][col] != 0;
}