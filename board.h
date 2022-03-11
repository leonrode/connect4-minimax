#ifndef BOARD_H
#define BOARD_H


class Board {
  public:
    Board();
    Board(const Board &other);
    bool placePiece(int color, int col);
    bool isColFull(int col);
    void print();
    int at(int r, int c);

    bool isBoardFull();

    int checkWin();

    bool canPlaceInColumn(int col);

    /*
      Determines if the current board is full or a player has won
    */
    bool isGameOver();

    /*
      Counts the number of three-in-a-rows by the specified color
    */
    int countThreeInARows(int color);
    int countTwoInARows(int color);
  private:
    int board[6][7];

    const int ROWS = 6;
    const int COLS = 7;


    const int RED = 2;
    const int YELLOW = 1;
};


#endif