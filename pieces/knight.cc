#include "knight.h"
#include "board.h"

Knight::Knight(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Knight::pieceType() const { return PieceType::Knight; }

vector<pair<char, int>> Knight::getMoves(Board &b) const {

}

int Knight::getWeight() const { return this->weight(); }
Colour Knight::getSide() const { return this->colour; }
pair<char, int> Knight::getCoords() const { return this->coords; }
void Knight::setCoords(pair<char, int> coords) { this->coords = coords; }

void Knight::notifyKing() {

}
