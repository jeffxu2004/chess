#include "knight.h"
#include "board.h"

Knight::Knight(int weight, Colour side. pair<char, int> coords) : weight{weight}, side{side}, coords{coords} {}

PieceType Knight::pieceType() const { return PieceType::Knight; }

vector<pair<char, int>> Knight::getMoves(Board &b) const {
	// Iterating through the possible moves for a knight is a bit annoying
	// so we use an array storing the possible ways a knight can move
	int possibleMoves[8][2] = {
		{-1, -2}, {1, -2},
		{2, -1}, {2, 1},
		{1, 2}, {-1, 2},
		{-2, 1}, {-2, -1}
	}
	
	vector<pair<char, int>> moves;
	vector<vector<unique_ptr<Piece>>> tempGrid = b.getGrid();	

	for (int i = 0; i < 8; i++) {
		// Check if move would be out of bounds
		int x = coords.first - 'a' possibleMoves[i][0];
		int y = coords.second - 1 + possibleMoves[i][1];
		if (x < 0 || x >= tempGrid.size() || y < 0 || y >= tempGrid.size()) continue;
		// Check if square is empty or opposing piece
		Piece pieceAtLoc = tempGrid[coords.first - 'a' + possibleMoves[i][0]][coords.second - 1 + possibleMoves[i][1]];
		if (pieceAtLoc.PieceType() == PieceType::None || pieceAtLoc.getColour() != this->colour) {
			moves.push_back(make_pair(static_cast<char>(x + 'a'), y + 1));
		}
	}
	return moves;
}

int Knight::getWeight() const { return this->weight(); }
Colour Knight::getSide() const { return this->colour; }
pair<char, int> Knight::getCoords() const { return this->coords; }
void Knight::setCoords(pair<char, int> coords) { this->coords = coords; }

void Knight::notifyKing() {

}
