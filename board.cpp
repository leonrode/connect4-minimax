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

int Board::countThreeInARows(int color) {

  int count = 0;
  // rows
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS - 2; col++) {
      if (board[row][col] != color) continue;
      if (board[row][col + 1] == color && board[row][col + 2] == color) {
        count++;
      }
    }
  }


  // cols
  for (int row = 0; row < ROWS - 2; row++) {
    for (int col = 0; col < COLS; col++) {
      if (board[row][col] != color) continue;

      if (board[row+1][col] == color && board[row+2][col] == color) {
        count++;
      }
    }
  }

  // up right diagonals
  for (int row = 2; row < ROWS; row++) {
    for (int col = 0; col < COLS - 2; col++) {
      if (board[row][col] != color) continue;

      if (board[row-1][col+1] == color && board[row-2][col+2] == color) {
        count++;
      }
    }
  }

  // down right diagonals
  for (int row = 0; row < ROWS - 2; row++) {
    for (int col = 0; col < COLS - 2; col++) {
      if (board[row][col] != color) continue;

      if (board[row+1][col+1] == color && board[row+2][col+2] == color) {
        count++;
      }
    }
  }

  return count;
}
int Board::countTwoInARows(int color) {

  int count = 0;
  // rows
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS - 1; col++) {
      if (board[row][col] != color) continue;
      if (board[row][col + 1] == color) {
        count++;
      }
    }
  }


  // cols
  for (int row = 0; row < ROWS - 1; row++) {
    for (int col = 0; col < COLS; col++) {
      if (board[row][col] != color) continue;

      if (board[row+1][col] == color) {
        count++;
      }
    }
  }

  // up right diagonals
  for (int row = 2; row < ROWS; row++) {
    for (int col = 0; col < COLS - 1; col++) {
      if (board[row][col] != color) continue;

      if (board[row-1][col+1] == color) {
        count++;
      }
    }
  }

  // down right diagonals
  for (int row = 0; row < ROWS - 1; row++) {
    for (int col = 0; col < COLS - 1; col++) {
      if (board[row][col] != color) continue;

      if (board[row+1][col+1] == color) {
        count++;
      }
    }
  }

  return count;
}


bool Board::placePiece(int color, int col) {
	if (isColFull(col)) return false;

	int r = 0;
	while (r < ROWS - 1 && board[r + 1][col] == 0) {
		r++;
	}

	board[r][col] = color;

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

bool Board::checkWin(int color) {
  // rows
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS - 3; col++) {
      if (board[row][col] != color) continue;

      if (board[row][col + 1] == color && board[row][col + 2] == color && board[row][col + 3] == color) {
        // std::cout << color << " row win.\n";
        return true;
      }
    }
  }

  // cols
  for (int row = 0; row < ROWS - 3; row++) {
    for (int col = 0; col < COLS; col++) {
      if (board[row][col] != color) continue;

      if (board[row+1][col] == color && board[row+2][col] == color && board[row+3][col] == color) {
        return true;
      }
    }
  }

  // up right diagonals
  for (int row = 3; row < ROWS; row++) {
    for (int col = 0; col < COLS -3; col++) {
      if (board[row][col] != color) continue;

      if (board[row-1][col+1] == color && board[row-2][col+2] == color && board[row-3][col+3] == color) {
        return true;
      }
    }
  }

  // down right diagonals
  for (int row = 0; row < ROWS - 3; row++) {
    for (int col = 0; col < COLS - 3; col++) {
      if (board[row][col] != color) continue;

      if (board[row+1][col+1] == color && board[row+2][col+2] == color && board[row+3][col+3] == color) {
        return true;
      }
    }
  }

  return false;
}

bool Board::isGameOver() {
  return isBoardFull() || checkWin(YELLOW) || checkWin(RED);
}