#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Knight: public Piece {
public:
	Knight(int weight, Colour side, pair<char, int> coords);
	vector<pair<char,int>> getMoves(const Board &b) const override;
	PieceType pieceType() const;
	int getWeight() const;
	Colour getSide() const;
	pair<char, int> getCoords() const;
	void setCoords(pair<char,int> coords);
};

#endif
