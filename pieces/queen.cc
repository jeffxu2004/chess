#include "queen.h"
#include "board.h"

Queen::Queen(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Queen::pieceType() const { return PieceType::Queen; }

vector<pair<char, int>> Queen::getMoves(Board &b) const {	
    vector<pair<char, int>> moves;
    vector<vector<unique_ptr<Piece>>> tempGrid = b.getGrid();
    
    // Check horizontal span of queen (left and right)
    for (int i = coords.first - 'a' - 1; i >= 0; i--) {
        // If empty square, add as possible move
        if (tempGrid[i][8 - coords.second].PieceType() == PieceType::None) {
            moves.push_back(make_pair(static_cast<char>(i+a), coords.second));
        } else {
            // Check if piece is opposing colour (can be taken)
            if (tempGrid[i][8 - coords.second].getColour() != this->colour) moves.push_back(make_pair(i, coords.second));
            break;
        }
    }
    for (int i = coords.first - 'a' + 1; i < tempGrid.size(); i++) {
        if (tempGrid[i][coords.second - 1].PieceType() == PieceType::None) {
            moves.push_back(make_pair(i, 8 - coords.second));
        } else {
            if (tempGrid[i][8 - coords.second].getColour() != this->colour) moves.push_back(make_pair(i, coords.second));
            break;
        }
    }

    // Check vertical span of queen (up and down)
    for (int i = 7 - coords.second; i >= 0; i--) {
        if (tempGrid[coords.first - 'a'][i].PieceType() == PieceType::None) {
            moves.push_back(make_pair(coords.first, i));
        } else {
            if (tempGrid[coords.first - 'a'][i].getColour() != this->colour) moves.push_back(make_pair(coords.first, i));
            break;
        }
    }
    for (int i = 9 - coords.second; i < tempGrid.size(); i++) {
        if (tempGrid[coords.first - 'a'][i].PieceType() == PieceType::None) {
            moves.push_back(make_pair(coords.first, i));
        } else {
            if (tempGrid[coords.first - 'a'][i].getColour() != this->colour) moves.push_back(make_pair(coords.first, i));
            break;
        }
    }	
	
    // Booleans indicating if the search has encountered end of board/a piece
    bool topleft = true, topright = true, bottomleft = true, bottomright = true;
    // Branch out and search the 4 diagonals like a breadth first search
    for (int i = 1; i < tempGrid.size(); i++) {
        if (topleft) {
            // Check if out of bounds
            if (coords.first - 'a' - i < 0 || 8 - coords.second - i < 0) {
                topleft = false;
            // If blank square add and keep going
            } else if (tempGrid[coords.first - 'a' - i][8 - coords.second - i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first - i, coords.second - i));
            // If opposing piece, add as possible move and stop iterating in this direction
            } else if (tempGrid[coords.first - 'a' - i][8 - coords.second - i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first - i, 8 - coords.second - i));
                topleft = false;
            // Hit own piece, stop iterating
            } else {
                topleft = false;
            }
        }
        if (topright) {
            if (coords.first - 'a' + i >= tempGrid.size() || 8 - coords.second - i < 0) {
                topright = false;
            } else if (tempGrid[coords.first - 'a' + i][8 - coords.second - i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first + i, coords.second - i));
            } else if (tempGrid[coords.first - 'a' + i][8 - coords.second - i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first + i, coords.second - i));
                topright = false;
            } else {
                topright = false;
            }

        }
        if (bottomleft) {
            if (coords.first - 'a' - i < 0 || 8 - coords.second + i >= tempGrid.size()) {
                bottomleft = false;
            } else if (tempGrid[coords.first - 'a' - i][8 - coords.second + i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first - i, coords.second + i));
            } else if (tempGrid[coords.first - 'a' - i][8 - coords.second + i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first - i, coords.second + i));
                bottomleft = false;
            } else {
                bottomleft = false;
            }
        }
        if (bottomright) {
            if (coords.first - 'a' + i >= tempGrid.size() || 8 - coords.second + i >= tempGrid.size()) {
                bottomright= false;
            } else if (tempGrid[coords.first - 'a' + i][8 - coords.second + i].PieceType() == PieceType::None) {
                moves.push_back(make_pair(coords.first + i, coords.second + i));
            } else if (tempGrid[coords.first - 'a' + i][8 - coords.second + i].getColour() != this->colour) {
                moves.push_back(make_pair(coords.first + i, coords.second + i));
                bottomright = false;
            } else {
                bottomright = false;
            }
        }
	}

	return moves;
}

int Queen::getWeight() const { return this->weight(); }
Colour Queen::getSide() const { return this->colour; }
pair<char, int> Queen::getCoords() const { return this->coords; }
void Queen::setCoords(pair<char, int> coords) { this->coords = coords; }

void Queen::notifyKing() {

}
