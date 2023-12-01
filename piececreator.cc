#include "piececreator.h"
using namespace std;

class PieceCreator {
public:
    static unique_ptr<Piece> createPiece(PieceType type, Colour side, pair<char, int> location) {
        switch (type) {
            case PieceType::Pawn:
                return make_unique<Pawn>(side, location);
            case PieceType::Rook:
                return make_unique<Rook>(side, location);
            case PieceType::Knight:
                return make_unique<Knight>(side, location);
            case PieceType::Bishop:
                return make_unique<Bishop>(side, location);
            case PieceType::Queen:
                return make_unique<Queen>(side, location);
            case PieceType::King:
                return make_unique<King>(side, location);
            default:
                return make_unique<Blank>(side, location);
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
