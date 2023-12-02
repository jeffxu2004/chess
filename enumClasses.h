#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H

#include <iostream>

using namespace std;

enum class Colour { White, Black, None };
enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King, Blank };
enum class Result { Win, Lose, Draw, Continue };

ostream& operator<<(ostream& out, PieceType type);
ostream& operator<<(ostream& out, Colour c);

// Extra Utility
ostream& operator<<(ostream& out, pair<char, int> move);
ostream& operator<<(ostream& out, pair<pair<char,int>, pair<char,int>> movePair);
#endif