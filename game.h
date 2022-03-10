#ifndef GAME_H
#define GAME_H

class Game {
	private:
		const int ROWS= 6;
		const int COLS = 7;
		int board[6][7];


	public:
		Game();
		bool placePiece(bool white, int col);
		bool isColFull(int col);
		void print();
};

#endif
