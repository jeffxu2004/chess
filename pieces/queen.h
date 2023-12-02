#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Queen: public Piece {
public:
	Queen(int weight, Colour side, pair<char, int> coords);
	vector<pair<char,int>> getMoves(const Board &b) const override;
	PieceType pieceType() const;
    int getWeight() const;
    Colour getSide() const;
    pair<char, int> getCoords() const;
    void setCoords(pair<char,int> coords);
};

#endif 