#include "enumClasses.h"

ostream& operator<<(ostream& out, PieceType type) {
    switch (type) {
        case PieceType::Pawn:
            out << "Pawn";
            return out;
        case PieceType::Bishop:
            out << "Bishop";
            return out;
        case PieceType::Queen:
            out << "Queen";
            return out;
        case PieceType::King:
            out << "King";
            return out;
        case PieceType::Blank:
            out << "Blank";
            return out;
        case PieceType::Knight:
            out << "Knight";
            return out;
        default:
            out << "Rook";
            return out;
    }

    return out;
}

ostream& operator<<(ostream& out, Colour c) {
    switch (c) {
        case Colour::White:
            out << "White";
            return out;
        case Colour::Black:
            out << "Black";
            return out;
        default:
            out << "None"; 
    }

    return out;
}

ostream& operator<<(ostream& out, pair<char,int> move) {
    out << "Coords: " << move.first << move.second;
    return out;
}

ostream& operator<<(ostream& out, pair<pair<char,int>,pair<char,int>> movePair) {
    out << "Start: " << movePair.first.first << movePair.first.second << " "
        << "End: " << movePair.second.first << movePair.second.second;
}
