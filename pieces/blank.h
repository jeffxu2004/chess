#include "piece.h"

class Board;

class Blank: public Piece {
public:
	Blank(int weight, Colour side);
	vector<pair<char,int>> getMoves(Board &b) const override;
	PieceType pieceType() const;
	int getWeight() const;
	Colour getSide() const;
	pair<char, int> getCoords() const;
	void setCoords(pair<char, int> coords);
};
