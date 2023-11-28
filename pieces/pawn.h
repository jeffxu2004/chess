#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Pawn: public Piece {
	bool moveTwo = true;
	bool beEnPas = false;

public:
	// Accessors (called in getMoves() before pawn move)
	bool canMoveTwo() const; // for moveTwo
	bool canBeEnPas() const; // for beEnPas
	
	// Mutators (called in getMoves() after the pawn is moved)
	void setMoveTwo(bool canMove) const; // for moveTwo
	void setEnPas(bool canEnPas) const; // for beEnPas
	
	PieceType pieceType() override;
	vector<pair<char, int>> getMoves(Board &);
};
