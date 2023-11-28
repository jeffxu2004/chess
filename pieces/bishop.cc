#include "bishop.h"
#include "board.h"

Bishop::Bishop(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Bishop::pieceType() const { return PieceType::Bishop; }

vector<pair<char, int>> Bishop::getMoves(Board &b) const {

}

int Bishop::getWeight() const { return this->weight(); }
Colour Bishop::getSide() const { return this->colour; }
pair<char, int> Bishop::getCoords() const { return this->coords; }
void Bishop::setCoords(pair<char, int> coords) { this->coords = coords; }

void Bishop::notifyKing() {

}
