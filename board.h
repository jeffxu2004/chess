#ifdef BOARD_H
#define BOARD_H

#include "subject.h"
#include <utility>
#include <vector>

enum PieceType { Pawn, Knight, Bishop, Rook, Queen, King, None };
enum Result { Win, Loss, Draw, Continue };

class Piece;

class Board : public Subject {
private:
	std::vector<std::vector<Piece*>> grid;
	Result state;
public:
	Board();
	Result getState();
	Piece* getPiece(pair<char, int> loc);
	void playMove(pair<char, int> start, pair<char, int> end);
	bool isValidMove(Piece *piece, pair<char, int> dest);
	void playMove(pair<char, int> start, pair<char, int> end, PieceType type);
	void isPromoting(pair<char, int> start, pair<char, int> end);
}

#endif
