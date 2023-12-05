#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H

#include <iostream>
#include <fstream>

using namespace std;

enum class Colour { White, Black, Neither };
enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King, Blank };
enum class Result { Win, Lose, Stalemate, Draw, Continue };
enum class Subscription { All, King };

ostream& operator<<(ostream& out, PieceType type);
ostream& operator<<(ostream& out, Colour c);

// Extra Utility
ostream& operator<<(ostream& out, pair<char, int> move);
ostream& operator<<(ostream& out, pair<pair<char,int>, pair<char,int>> movePair);
#endif