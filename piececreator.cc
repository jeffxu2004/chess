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
};
