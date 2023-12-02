#include "knight.h"
#include "../board.h"

Knight::Knight(int weight, Colour side, pair<char, int> coords) : Piece{weight, side, coords} {}

PieceType Knight::pieceType() const { return PieceType::Knight; }

vector<pair<char, int>> Knight::getMoves(const Board &b) const {
	// Iterating through the possible moves for a knight is a bit annoying
	// so we use an array storing the possible ways a knight can move
	int possibleMoves[8][2] = {
		{-1, -2}, {1, -2},
		{2, -1}, {2, 1},
		{1, 2}, {-1, 2},
		{-2, 1}, {-2, -1}
	};
	
	vector<pair<char, int>> moves;
	vector<vector<Piece*>> tempGrid = b.getGrid();	

	for (int i = 0; i < 8; i++) {
		// Check if move would be out of bounds
		int x = coords.first - 'a' + possibleMoves[i][0];
		int y = 8 - coords.second - possibleMoves[i][1];
		if (x < 0 || x >= int(tempGrid.size()) || y < 0 || y >= int(tempGrid.size())) continue;
		// Check if square is empty or opposing piece
		Piece* pieceAtLoc = tempGrid[x][y];
		if (pieceAtLoc->pieceType() == PieceType::Blank || pieceAtLoc->getSide() != this->side) {
			moves.push_back(make_pair(static_cast<char>(x + 'a'), 8 - y));
		}
	}
	return moves;
}

int Knight::getWeight() const { return this->weight; }
Colour Knight::getSide() const { return this->side; }
pair<char, int> Knight::getCoords() const { return this->coords; }
void Knight::setCoords(pair<char, int> coords) { this->coords = coords; }