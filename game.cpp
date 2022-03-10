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
