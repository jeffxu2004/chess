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
	vector<vector<unique_ptr<Piece>>> tempGrid = b.getGrid();

	// Set direction based on colour, black is negative, white is positive
	int direction = colour==Colour::WHITE?1:-1;

	// Move forward
	if (tempGrid[coords.first - 'a'][coords.second - 1 + direction].pieceType() == PieceType::None) {
		moves.push_back(make_pair(coords.first, coords.second + direction));
		// Check if piece can move two squares on first move
		if (moveTwo && tempGird[coords.first - 'a'][coords.second - 1 + 2*direction].pieceType() == pieceType::None) {
			moves.push_back();
			moveTwo = false;
		}
	}
	
	// Take pieces
	for (int i = -1; i < 1; i+=2) {
		Piece piece = tempGird[coords.first - 'a' + i][coords.second - 1 + direction]; 
		if (piece.pieceType() != PieceType::None && piece.getColour() != colour) {
			moves.push_back(static_cast<char>(coords.first + i), coords.second + direction);
		}	
	}
	
	return moves;
}

int Pawn::getWeight() const { return this->weight; }
Colour Pawn::getSide() const { return this->colour; }
pair<char, int> Pawn::getCoords() const { return this->coords; }
void Pawn::setCoords(pair<char, int> coords) { this->coords = coords; }

void Pawn::notifyKing() {
	// Justin!
}
