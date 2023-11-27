#ifndef PIECE_H
#define PIECE_H

#include "subject.h"

enum class Colour { White, Black };

class Piece : public Subject {
private:
	string pieceType;
	int weight;
	Colour side;
public:
	Piece(string pieceType, int weight, Colour side) : weight{weight}, side{side} {}
	virtual ~Piece() = default;
	int getWeight() const;
	Colour getSide() const;
	string getPieceType() const;
	void notifyObservers();
}

#endif
