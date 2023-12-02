#include "enumClasses.h"

ostream& operator<<(ostream& out, PieceType type) {
    switch (type) {
        case PieceType::Pawn:
            out << "Pawn" << endl;
            return out;
        case PieceType::Bishop:
            out << "Bishop" << endl;
            return out;
        case PieceType::Queen:
            out << "Queen" << endl;
            return out;
        case PieceType::King:
            out << "King" << endl;
            return out;
        case PieceType::Blank:
            out << "Blank" << endl;
            return out;
        case PieceType::Knight:
            out << "Knight" << endl;
            return out;
        default:
            out << "Rook" << endl;
            return out;
    }

    return out;
}

ostream& operator<<(ostream& out, Colour c) {
    switch (c) {
        case Colour::White:
            out << "White" << endl;
            return out;
        case Colour::Black:
            out << "Black" << endl;
            return out;
        default:
            out << "None" << endl; 
    }

    return out;
}

ostream& operator<<(ostream& out, pair<char,int> move) {
    out << "Move: " << move.first << move.second << endl;
    return out;
}

ostream& operator<<(ostream& out, pair<pair<char,int>,pair<char,int>> movePair) {
    out << "Start: " << movePair.first.first << movePair.first.second << " "
        << "End: " << movePair.second.first << movePair.second.second << endl;
}