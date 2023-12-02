#include "pawn.h"
#include "../board.h"

Pawn::Pawn(int weight, Colour side, pair<char,int> coords) : Piece{weight, side, coords} {};

bool Pawn::canMoveTwo() const {	return moveTwo; }
bool Pawn::canBeEnPas() const { return beEnPas; }
void Pawn::setMoveTwo(bool canMove) { moveTwo = canMove; }
void Pawn::setEnPas(bool canEnPas) { beEnPas = canEnPas; }

PieceType Pawn::pieceType() const { return PieceType::Pawn; }

vector<pair<char,int>> Pawn::getMoves(const Board &b) const {
	vector<pair<char,int>> moves;
	vector<vector<Piece*>> tempGrid = b.getGrid();

	// Set direction based on colour, white is negative, black is positive (not based on chess notation, based on array indexing)
	int direction = side==Colour::White?-1:1;

	// Move forward
	if (tempGrid[coords.first - 'a'][8 - coords.second + direction]->pieceType() == PieceType::Blank) {
		moves.push_back(make_pair(coords.first, coords.second + direction));
		// Check if piece can move two squares on first move
		if (moveTwo && tempGrid[coords.first - 'a'][8 - coords.second + 2*direction]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(coords.first, coords.second - 2*direction));
		}
	}
	
	// Take pieces
	for (int i = -1; i < 1; i+=2) {
		Piece* piece = tempGrid[coords.first - 'a' + i][8 - coords.second + direction];
		if (piece->pieceType() != PieceType::Blank && piece->getSide() != side) {
			moves.push_back(make_pair(static_cast<char>(coords.first + i), coords.second - direction));
		}
		// En passant
		piece = tempGrid[coords.first - 'a' + i][8 - coords.second];
		if (piece->pieceType() == PieceType::Pawn && piece->getSide() != side && dynamic_cast<Pawn*>(piece)->canBeEnPas()) {
			moves.push_back(make_pair(static_cast<char>(coords.first + i), coords.second - direction));
		}
	}

	return moves;
}

int Pawn::getWeight() const { return this->weight; }
Colour Pawn::getSide() const { return this->side; }
pair<char, int> Pawn::getCoords() const { return this->coords; }
void Pawn::setCoords(pair<char, int> coords) { this->coords = coords; }