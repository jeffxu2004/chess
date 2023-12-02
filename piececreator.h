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

using namespace std;

class PieceCreator {
public:
    static unique_ptr<Piece> createPiece(PieceType type, Colour side, pair<char, int> location) {
        switch (type) {
            case PieceType::Pawn:
                return make_unique<Pawn>(1, side, location);
            case PieceType::Rook:
                return make_unique<Rook>(5, side, location);
            case PieceType::Knight:
                return make_unique<Knight>(3, side, location);
            case PieceType::Bishop:
                return make_unique<Bishop>(3, side, location);
            case PieceType::Queen:
                return make_unique<Queen>(9, side, location);
            case PieceType::King:
                return make_unique<King>(100, side, location);
            default:
                return make_unique<Blank>(0, side, location);
        }
    }

    static unique_ptr<Piece> makePieceType(PieceType type, Colour side, pair<char, int> location) {
        switch (type) {
            case PieceType::Pawn:
                return make_unique<Pawn>(1, side, location);
            case PieceType::Rook:
                return make_unique<Rook>(5, side, location);
            case PieceType::Knight:
                return make_unique<Knight>(3, side, location);
            case PieceType::Bishop:
                return make_unique<Bishop>(3, side, location);
            case PieceType::Queen:
                return make_unique<Queen>(9, side, location);
            case PieceType::King:
                return make_unique<King>(100, side, location);
            default:
                return make_unique<Blank>(0, side, location);
        }
    }

    static unique_ptr<Piece> setPiece(char pieceChar, pair<char, int> location) {
        Colour side = isupper(pieceChar) ? Colour::White : Colour::Black;
        pieceChar = tolower(pieceChar);

        switch (pieceChar) {
            case 'p':
                return make_unique<Pawn>(1, side, location);
            case 'r':
                return make_unique<Rook>(5, side, location);
            case 'n':
                return make_unique<Knight>(3, side, location);
            case 'b':
                return make_unique<Bishop>(3, side, location);
            case 'q':
                return make_unique<Queen>(9, side, location);
            case 'k':
                return make_unique<King>(100, side, location);
            default:
                return make_unique<Blank>(0, side, location);
        }
    }

    static char createPiece(PieceType type, Colour side, bool isDark) {
        switch (type) {
            case PieceType::Pawn:
                if (side == Colour::Black)
                    return 'p';
                else if (side == Colour::White)
                    return 'P';
            case PieceType::Rook:
                if (side == Colour::Black)
                    return 'r';
                else if (side == Colour::White)
                    return 'R';
            case PieceType::Knight:
                if (side == Colour::Black)
                    return 'n';
                else if (side == Colour::White)
                    return 'N';
            case PieceType::Bishop:
                if (side == Colour::Black)
                    return 'b';
                else if (side == Colour::White)
                    return 'B';
            case PieceType::Queen:
                if (side == Colour::Black)
                    return 'q';
                else if (side == Colour::White)
                    return 'Q';
            case PieceType::King:
                if (side == Colour::Black)
                    return 'k';
                else if (side == Colour::White)
                    return 'K';
            default:
                return (isDark ? '_' : ' ');
        }
    }
};

#endif