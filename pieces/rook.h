#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Rook: public Piece {
	bool castle = true;

public:
	bool canCastle() const;

	void setCastle(bool castleState);

	vector<pair<char,int>> getMoves(Board &b) const override;

	PieceType pieceType() const;
};
