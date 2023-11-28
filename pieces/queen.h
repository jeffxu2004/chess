#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

class Board;

class Queen: public Piece {
public:
	vector<pair<char,int>> getMoves(Board &b) const override;
	PieceType pieceType() const;
};
