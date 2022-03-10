#include <iostream>

#include "game.h"


int main() {
	Game game;

	game.placePiece(true, 0);
	game.placePiece(false, 0);
	game.placePiece(true, 0);
	game.print();
}
