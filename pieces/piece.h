#ifndef PIECE_H
#define PIECE_H

#include "../subject.h"

enum class Colour { White, Black, None};

class Piece : public Subject {
	int weight;
	Colour side;
public:
	Piece(int weight, Colour side); // ctor
	~Piece() = default; // dtor
	

	int getWeight() const; // returns weight of piece
	
	// returns the value of the 'side' field
	Colour getSide() const;

	// Pure virtual function to make Piece an abstract class.
	// Each concrete subclass of Piece will return their corresponding pieceType value
	virtual PieceType pieceType() const = 0;

	// Pieces must notify the king if they move in/out of the king's check-able squares.
	// Each checkable square is setup upon board initialization and is changed when:
	//    * the king moves
	//    * a piece moves into the check-able squares (resulting in some of the original squares to be blocked
	//    * a pieces moves out of the check-able squares (resulting in new squares that are check-able)
	void notifyKing();
}

#endif