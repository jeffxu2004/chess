#include "bishop.h"
#include "board.h"

Bishop::Bishop(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Bishop::pieceType() const { return PieceType::Bishop; }

vector<pair<char, int>> Bishop::getMoves(Board &b) const {
    vector<pair<char, int>> moves;
    vector<vector<unique_ptr<Piece>>> tempGrid = b.getGrid();
    
	// Booleans indicating if the search has encountered end of board/a piece
	bool topleft = true, topright = true, bottomleft = true, bottomright = true;
	// Branch out and search the 4 diagonals like a breadth first search
	for (int i = 1; i < tempGrid.size(); i++) {
		if (topleft) {
			// Check if out of bounds
			if (coords.first - 'a' - i < 0 || coords.second - 1 - i < 0) {
				topleft = false;
			// If blank square add and keep going
			} else if (tempGrid[coords.first - 'a' - i][coords.second - 1 - i].PieceType() == PieceType::None) {
				moves.push_back(make_pair(coords.first - i, coords.second - i));
			// If opposing piece, add as possible move and stop iterating in this direction
			} else if (tempGrid[coords.first - 'a' - i][coords.second - 1 - i].getColour() != this->colour) {
				moves.push_back(make_pair(coords.first - i, coords.second - i));
				topleft = false;
			// Hit own piece, stop iterating
			} else {
				topleft = false;
			}
		}
		if (topright) {
            if (coords.first - 'a' + i >= tempGrid.size() || coords.second - 1 - i < 0) {
                topright = false;
            } else if (tempGrid[coords.first - 'a' + i][coords.second - 1 - i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first + i, coords.second - i));
            } else if (tempGrid[coords.first - 'a' + i][coords.second - 1 - i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first + i, coords.second - i));
                topright = false;
            } else {
                topright = false;
            }

		}
		if (bottomleft) {
            if (coords.first - 'a' - i < 0 || coords.second - 1 + i >= tempGrid.size()) {
                bottomleft = false;
            } else if (tempGrid[coords.first - 'a' - i][coords.second - 1 + i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first - i, coords.second + i));
            } else if (tempGrid[coords.first - 'a' - i][coords.second - 1 + i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first - i, coords.second + i));
                bottomleft = false;
            } else {
                bottomleft = false;
            }
		}
		if (bottomright) {
            if (coords.first - 'a' + i >= tempGrid.size() || coords.second - 1 + i >= tempGrid.size()) {
                bottomright= false;
            } else if (tempGrid[coords.first - 'a' + i][coords.second - 1 + i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first + i, coords.second + i));
            } else if (tempGrid[coords.first - 'a' + i][coords.second - 1 + i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first + i, coords.second + i));
                bottomright = false;
            } else {
                bottomright = false;
            }
		}
	} 

    return moves;
}

int Bishop::getWeight() const { return this->weight(); }
Colour Bishop::getSide() const { return this->colour; }
pair<char, int> Bishop::getCoords() const { return this->coords; }
void Bishop::setCoords(pair<char, int> coords) { this->coords = coords; }

void Bishop::notifyKing() {

}