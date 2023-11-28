#include "piece.h"

class Board;

class Blank: public Piece {
public:
	vector<pair<char,int>> getMoves(Board &b) const override;
	PieceType pieceType() const;	
};
