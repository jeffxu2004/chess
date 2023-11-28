#ifdef BOARD_H
#define BOARD_H

#include "subject.h"
#include <utility>
#include <vector>

using namespace std;

enum Result { Win, Loss, Draw, Continue };

class Piece;

class Board : public Subject {
	vector<vector<Piece*>> grid;
	Result state;
public:
	Board(); // ctor
	
	// returns the state field
	Result getState();

	// returns a pointer to the piece at the specified coordinate on the square.
	Piece* getPiece(pair<char, int> loc);

	// takes in a start coordinate which indicates which piece is being moved and moves it to the 
	// end coordinate. This function is called in main once it is determined that the move is valid
	// and it notifies observers (i.e. board and king if necessary)
	void playMove(pair<char, int> start, pair<char, int> end);

	// returns true if dest is a square that piece can legally move to and false otherwise.
	// This function calls the getMoves() function in piece to get a vector<pair> and checks
	// whether dest is in the vector.
	bool isValidMove(Piece *piece, pair<char, int> dest);

	// playMove is overloarded for pawn promotion. If the pawn is promoting, the desired piece that
	// it promotes into is passed into the function as an additional parameter.
	void playMove(pair<char, int> start, pair<char, int> end, PieceType type);

	// returns true if the piece is a pawn and is promoting and false otherwise.
	bool isPromoting(pair<char, int> start, pair<char, int> end);
}

#endif
