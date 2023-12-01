#include "rook.h"
#include "board.h"

Rook::Rook(int weight, Colour side, pair<char, int> coords) : Piece{weight, side, coords} {}

PieceType Rook::pieceType() const { return PieceType::Rook; }

bool Rook::hasMoved() const {
	return moved;
}

void Rook::setCastle(bool castleState) {
	moved = true;
}

vector<pair<char, int>> Rook::getMoves(const Board &b) const {
	vector<pair<char, int>> moves;
	vector<vector<Piece*>> tempGrid = b.getGrid();
	// Check horizontal span of rook (left and right)
	for (int i = coords.first - 'a' - 1; i >= 0; i--) {
		// If empty square, add as possible move
		if (tempGrid[i][8 - coords.second]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(static_cast<char>(i+'a'), coords.second));
		} else {
			// Check if piece is opposing colour (can be taken)
            if (tempGrid[i][8 - coords.second]->getSide() != this->side) moves.push_back(make_pair(i, coords.second));
			break;
		}
	}
	for (int i = coords.first - 'a' + 1; i < tempGrid.size(); i++) {
		if (tempGrid[i][coords.second - 1]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(i, 8 - coords.second));
		} else {
			if (tempGrid[i][8 - coords.second]->getSide() != this->side) moves.push_back(make_pair(i, coords.second));
			break;
		}
	}

	// Check vertical span of rook (up and down)
	for (int i = 7 - coords.second; i >= 0; i--) {
		if (tempGrid[coords.first - 'a'][i]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(coords.first, i));
		} else {
            if (tempGrid[coords.first - 'a'][i]->getSide() != this->side) moves.push_back(make_pair(coords.first, i));
			break;
		}
	}
	for (int i = 9 - coords.second; i < tempGrid.size(); i++) {
		if (tempGrid[coords.first - 'a'][i]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(coords.first, i));
		} else {
            if (tempGrid[coords.first - 'a'][i]->getSide() != this->side) moves.push_back(make_pair(coords.first, i));
			break;
		}
	}
	
	return moves;
}

int Rook::getWeight() const { return this->weight; }
Colour Rook::getSide() const { return this->side; }
pair<char, int> Rook::getCoords() const { return this->coords; }
void Rook::setCoords(pair<char, int> coords) { this->coords = coords; }