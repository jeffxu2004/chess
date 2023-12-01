#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Rook: public Piece {
	bool moved = true;

public:
	Rook(int weight, Colour side, pair<char, int> coords);
	bool hasMoved() const;
	void setCastle(bool castleState);

	vector<pair<char,int>> getMoves(const Board &b) const override;

	PieceType pieceType() const;
    int getWeight() const;
    Colour getSide() const;
    pair<char, int> getCoords() const;
    void setCoords(pair<char,int> coords);
};
