#include "piece.h"

class Board;

class Blank: public Piece {
public:
	Blank(int weight, Colour side, pair<char, int> coords);
	PieceType pieceType() const;
	int getWeight() const;
	Colour getSide() const;
	pair<char, int> getCoords() const;
	vector<pair<char,int>> getMoves(const Board &) const override;
	void setCoords(pair<char, int> coords);
};