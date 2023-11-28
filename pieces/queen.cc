#include "queen.h"
#include "board.h"

Queen::Queen(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Queen::pieceType() const { return PieceType::Queen; }

vector<pair<char, int>> Queen::getMoves(Board &b) const {

}

int Queen::getWeight() const { return this->weight(); }
Colour Queen::getSide() const { return this->colour; }
pair<char, int> Queen::getCoords() const { return this->coords; }
void Queen::setCoords(pair<char, int> coords) { this->coords = coords; }

void Queen::notifyKing() {

}
