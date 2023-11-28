#include "piececreator.h"

Piece PieceCreator::createPiece(PieceType type, Colour side, std::pair<char, int> location) {
	switch (type) {
		case PieceType::Pawn:
            return Pawn(side, location);
		case PieceType::Rook:
            return Rook(side, location);
		case PieceType::Knight:
            return Knight(side, location);
		case PieceType::Bishop:
            return Bishop(side, location);
		case PieceType::Queen:
            return Queen(side, location);
		case PieceType::King:
            return King(side, location);
		default:
            return Blank(side, location);
    }
}
