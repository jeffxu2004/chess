#ifndef PIECE_CREATOR_H
#define PIECE_CREATOR_H

#include <string>
#include "pieces/piece.h"
#include <memory>
#include "pieces/blank.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"

class PieceCreator {
public:	
	static std::unique_ptr<Piece> createPiece(PieceType type, Colour side, pair<char, int> location);
	static char createPiece(PieceType type, Colour side, bool isDark);
};

#endif
