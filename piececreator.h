#ifndef PIECE_CREATOR_H
#define PIECE_CREATOR_H

#include <string>
#include <piece.h>
#include <memory>
#include "blank.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

class PieceCreator {
public:	
	static std::unique_ptr<Piece> createPiece(PieceType type, Colour side, pair<char, int> location);
	static char createPiece(PieceType type, Colour side, bool isDark);
};

#endif
