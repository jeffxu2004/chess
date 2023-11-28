#include "piece.h"

class Blank: public Piece {
public:
	<vector<pair<char,int>> getMoves(Board &b) const;
	PieceType pieceType() const;	
};
