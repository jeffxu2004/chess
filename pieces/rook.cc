#include "rook.h"
#include "board.h"

Rook::Rook(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Rook::pieceType() const { return PieceType::Rook; }

bool Rook::canMove() const {
	return moved;
}

void Rook::setCastle(bool castleState) {
	moved = true;
}

vector<pair<char, int>> Rook::getMoves(Board &b) const {
	vector<pair<char, int>> moves;
	vector<vector<unique_ptr<Piece>>> tempGrid = b.getGrid();
	// Check horizontal span of rook (left and right)
	for (int i = coords.first - 'a' - 1; i >= 0; i--) {
		// If empty square, add as possible move
		if (tempGrid[i][8 - coords.second]->PieceType() == PieceType::None) {
			moves.push_back(make_pair(static_cast<char>(i+a), coords.second));
		} else {
			// Check if piece is opposing colour (can be taken)
            if (tempGrid[i][8 - coords.second]->getColour() != this->colour) moves->push_back(make_pair(i, coords.second));
			break;
		}
	}
	for (int i = coords.first - 'a' + 1; i < tempGrid.size(); i++) {
		if (tempGrid[i][coords.second - 1]->PieceType() == PieceType::None) {
			moves.push_back(make_pair(i, 8 - coords.second));
		} else {
			if (tempGrid[i][8 - coords.second]->getColour() != this->colour) moves.push_back(make_pair(i, coords.second));
			break;
		}
	}

	// Check vertical span of rook (up and down)
	for (int i = 7 - coords.second; i >= 0; i--) {
		if (tempGrid[coords.first - 'a'][i]->PieceType() == PieceType::None) {
			moves.push_back(make_pair(coords.first, i));
		} else {
            if (tempGrid[coords.first - 'a'][i]->getColour() != this->colour) moves.push_back(make_pair(coords.first, i));
			break;
		}
	}
	for (int i = 9 - coords.second; i < tempGrid.size(); i++) {
		if (tempGrid[coords.first - 'a'][i]->PieceType() == PieceType::None) {
			moves.push_back(make_pair(coords.first, i));
		} else {
            if (tempGrid[coords.first - 'a'][i]->getColour() != this->colour) moves.push_back(make_pair(coords.first, i));
			break;
		}
	}
	
	return moves;
}

int Rook::getWeight() const { return this->weight(); }
Colour Rook::getSide() const { return this->colour; }
pair<char, int> Rook::getCoords() const { return this->coords; }
void Rook::setCoords(pair<char, int> coords) { this->coords = coords; }

void Rook::notifyKing() {

}
