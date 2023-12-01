#ifndef PIECE_H
#define PIECE_H

#include "../subject.h"
#include <vector>
#include <utility>

using namespace std;

enum class Colour { White, Black, None};

class Piece : public Subject {
protected:	
	int weight;
	Colour side;
	pair<char,int> coords;
public:
	Piece(int weight, Colour side, pair<char,int> coords); // ctor
	virtual ~Piece() = default; // dtor
	
	int getWeight() const; // returns weight of piece
	
	// returns the value of the 'side' field
	Colour getSide() const;

	// Pure virtual function to make Piece an abstract class.
	// Each concrete subclass of Piece will return their corresponding pieceType value
	virtual PieceType pieceType() const = 0;

	virtual vector<pair<char, int>> getMoves(const Board &b) const = 0;

	pair<char,int> getCoords() const;

	void setCoords(pair<char,int> coords);

	// operator overload to check if the piece is the same
	bool operator==(Piece* other);
};

#endif
