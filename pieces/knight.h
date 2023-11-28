#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Knight: public Piece {
public:
	vector<pair<char,int>> getMoves(Board &b) const;
	PieceType pieceType() const;	
};
