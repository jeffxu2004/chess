#ifndef PIECE_CREATOR_H
#define PIECE_CREATOR_H

#include <string>
#include <piece.h>
#include "none.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

class PieceCreator {
public:	
	static Piece createPiece(PieceType type, Colour side, pair<char, int> location);
}

#endif
