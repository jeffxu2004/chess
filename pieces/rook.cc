#include "rook.h"
#include "board.h"

Rook::Rook(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Rook::pieceType() const { return PieceType::Rook; }

bool Rook::canMove() const {
	return moved;
}

void Rook::setCastle(bool castleState) {
	moved = true;
	// Is moved supposed to be true by default in .h file?
}

vector<pair<char, int>> Rook::getMoves(Board &b) const {

}

int Rook::getWeight() const { return this->weight(); }
Colour Rook::getSide() const { return this->colour; }
pair<char, int> Rook::getCoords() const { return this->coords; }
void Rook::setCoords(pair<char, int> coords) { this->coords = coords; }

void Rook::notifyKing() {

}
