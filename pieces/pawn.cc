#include "pawn.h"
#include "board.h"

Pawn::Pawn(int weight = 1, Colour side, pair<char,int> coords) : weight{weight}, side{side}, coords{coords} {};

bool Pawn::canMoveTwo() const {	return moveTwo; }
bool Pawn::canBeEnPas() const { return beEnPas; }
void Pawn::setMoveTwo(bool canMove) { moveTwo = canMove; }
void Pawn::setEnPas(bool canEnPas) { beEnPas = canEnPas; }

PieceType Pawn::pieceType() const { return PieceType::Pawn; }

vector<pair<char,int>> Pawn::getMoves(Board &b) {
	vector<pair<<char,int>> moves;
	
	return moves;
}

int Pawn::getWeight() const { return this->weight; }
Colour Pawn::getSide() const { return this->colour; }
pair<char, int> Pawn::getCoords() const { return this->coords; }
void Pawn::setCoords(pair<char, int> coords) { this->coords = coords; }

void Pawn::notifyKing() {
	// Justin!
}
