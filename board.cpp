#include "board.h"
#include <iostream>
Board::Board() {
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      board[r][c] = 0;
    }
  }
}

Board::Board(const Board &other) {
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      board[r][c] = other.board[r][c];
    }
  }


}
void Board::print() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			std::cout << board[r][c] << " ";
		}
		std::cout << std::endl;
	}
}


bool Board::placePiece(int color, int col) {
	if (isColFull(col)) return false;

	int r = 0;
	while (r < ROWS - 1 && board[r + 1][col] == 0) {
		r++;
	}

	board[r][col] = color == RED ? 2 : 1;

	return true;
}


bool Board::isColFull(int col) {
	return board[0][col] != 0;
}

int Board::at(int r, int c) {
  return board[r][c];
}

bool Board::isBoardFull() {
  for (int c = 0; c < COLS; c++) {
    if (board[0][c] == 0) return false;
  }

  return true;
}


bool Board::canPlaceInColumn(int col) {
  return board[0][col] == 0;
}

int Board::checkWin() {
  // rows
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS - 3; col++) {
      if (board[row][col] == 0) continue;
      int cur = board[row][col];
      if (board[row][col + 1] == cur && board[row][col + 2] == cur && board[row][col + 3] == cur) {
        return cur;
      }
    }
  }

  // cols
  for (int row = 0; row < ROWS - 3; row++) {
    for (int col = 0; col < COLS; col++) {
      if (board[row][col] == 0) continue;
      int cur = board[row][col];
      if (board[row+1][col] == cur && board[row+2][col] == cur && board[row+3][col] == cur) {
        return cur;
      }
    }
  }

  // up right diagonals
  for (int row = 3; row < ROWS; row++) {
    for (int col = 0; col < COLS -3; col++) {
      if (board[row][col] == 0) continue;
      int cur = board[row][col];
      if (board[row-1][col+1] == cur && board[row-2][col+2] == cur && board[row-3][col+3] == cur) {
        return cur;
      }
    }
  }

  // down right diagonals
  for (int row = 0; row < ROWS - 3; row++) {
    for (int col = 0; col < COLS - 3; col++) {
      if (board[row][col] == 0) continue;
      int cur = board[row][col];
      if (board[row+1][col+1] == cur && board[row+2][col+2] == cur && board[row+3][col+3] == cur) {
        return cur;
      }
    }
  }

  return -1;
}

bool Board::isGameOver() {
  return isBoardFull() || checkWin();
}