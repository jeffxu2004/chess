#include "blank.h"
#include "../board.h"

Blank::Blank(int weight = 0, Colour side, pair<char, int> coords) : Piece{weight, side, coords} {}

PieceType Blank::pieceType() const { return PieceType::Blank; }
int Blank::getWeight() const { return this->weight; }
Colour Blank::getSide() const { return this->side; }
pair<char, int> Blank::getCoords() const { return this->coords; }
void Blank::setCoords(pair<char, int> coords) { this->coords = coords; }
