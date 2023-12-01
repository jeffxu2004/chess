#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Pawn: public Piece {
	bool moveTwo = true;
	bool beEnPas = false;

public:
	Pawn(int weight, Colour side, pair<char,int> coords);
	// Accessors (called in getMoves() before pawn move)
	bool canMoveTwo() const; // for moveTwo
	bool canBeEnPas() const; // for beEnPas
	
	// Mutators (called in getMoves() after the pawn is moved)
	void setMoveTwo(bool canMove) const; // for moveTwo
	void setEnPas(bool canEnPas) const; // for beEnPas
	
	PieceType pieceType() const override;
	vector<pair<char, int>> getMoves(const Board &b) const override;
	int getWeight() const;
	Colour getSide() const;
	pair<char,int> getCoords() const;
	void setCoords(pair<char,int> coords);
	
	void notifyKing();
};
