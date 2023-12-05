#include "rook.h"
#include "../board.h"

Rook::Rook(int weight, Colour side, pair<char, int> coords) : Piece{weight, side, coords} {}

PieceType Rook::pieceType() const { return PieceType::Rook; }

bool Rook::hasMoved() const {
	return moved;
}

void Rook::setMoved(bool castleState) {
	moved = castleState;
}

vector<pair<char, int>> Rook::getMoves(const Board &b) const {
	vector<pair<char, int>> moves;
	vector<vector<Piece*>> tempGrid = b.getGrid();
	
	// Check horizontal span of rook (left and right)
	for (int i = coords.first - 'a' - 1; i >= 0; i--) {
		// If empty square, add as possible move
		if (tempGrid[8 - coords.second][i]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(static_cast<char>(i+'a'), coords.second));
		} else {
			// Check if piece is opposing colour (can be taken)
            if (tempGrid[8 - coords.second][i]->getSide() != this->side) moves.push_back(make_pair(static_cast<char>(i+'a'), coords.second));
			break;
		}
	}
	for (int i = coords.first - 'a' + 1; i < tempGrid.size(); i++) {
		if (tempGrid[8 - coords.second][i]->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(static_cast<char>(i+'a'), coords.second));
		} else {
			if (tempGrid[8 - coords.second][i]->getSide() != this->side) moves.push_back(make_pair(static_cast<char>(i+'a'), coords.second));
			break;
		}
	}

	// Check vertical span of rook (up and down)
	for (int i = 1; 8 - coords.second - i >= 0; i++) {
		if (tempGrid[8 - coords.second - i][coords.first - 'a']->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(coords.first, coords.second + i));
		} else {
            if (tempGrid[8 - coords.second - i][coords.first - 'a']->getSide() != this->side) moves.push_back(make_pair(coords.first, coords.second + i));
			break;
		}
	}
	for (int i = 1; 8 - coords.second + i < tempGrid.size(); i++) {
		if (tempGrid[8 - coords.second + i][coords.first - 'a']->pieceType() == PieceType::Blank) {
			moves.push_back(make_pair(coords.first, coords.second - i));
		} else {
            if (tempGrid[8 - coords.second + i][coords.first - 'a']->getSide() != this->side) moves.push_back(make_pair(coords.first, coords.second - i));
			break;
		}
	}
	
	return moves;
}

int Rook::getWeight() const { return this->weight; }
Colour Rook::getSide() const { return this->side; }
pair<char, int> Rook::getCoords() const { return this->coords; }
void Rook::setCoords(pair<char, int> coords) { this->coords = coords; }
