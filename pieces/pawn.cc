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
	int row = 8 - coords.second + direction;

	// Move forward
	if (tempGrid[row][coords.first - 'a']->pieceType() == PieceType::Blank) {
		moves.push_back(make_pair(coords.first, coords.second - direction));
		// Check if piece can move two squares on first move
		char c = coords.first - 'a';
		int n = 8-coords.second + 2*direction;
		if (moveTwo) {
			// Check if piece is in the correct starting position to move two
			if (((this->side == Colour::White && this->coords.second == 2) ||
				(this->side == Colour::Black && this->coords.second == 7)) &&
				tempGrid[8 - coords.second + 2*direction][coords.first - 'a']->pieceType() == PieceType::Blank) {
				moves.push_back(make_pair(coords.first, coords.second - 2*direction));
			}
		}
	}
	
	// Take pieces
	for (int i = -1; i <= 1; i+=2) {
		int x = int(coords.first - 'a' + i);
		int y = 8 - coords.second + direction;
		if (x < 0 || x > 7 || y < 0 || y > 7) continue;
		Piece* piece = tempGrid[8 - coords.second + direction][coords.first - 'a' + i];
		if (piece->pieceType() != PieceType::Blank && piece->getSide() != side) {
			moves.push_back(make_pair(static_cast<char>(coords.first + i), coords.second - direction));
		}
		// En passant
		piece = tempGrid[8 - coords.second][coords.first - 'a' + i];
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
