#include "chessbot.h"
#include <cstdlib>
#include <limits>

class LevelThree : ChessBot {
    // Takes in the grid and a pair indicating the destination of the move in question
    // This function returns zero if the destination is an empty square, otherwise it returns
    // the weight of the piece taken.
    // Checks have a weight of two. (If a move takes a piece and checks the enemy king, the weight is summed)
    int weightOfMove(vector<vector<unique_ptr<Piece>>> &g, pair<char, int> dest) {
        int weight = g[dest.first - 'a'][8 - dest.second].getWeight();
        int check = 0;
        return weight + check;
    }

	// Takes in a copy of the board and a pair indicating the destination of the move in question
	// Checks through all of opponents moves to see what their most valuable move is
	// Then returns the difference between bot's move and opponents move
	int valueOfMove(Board b, pair<char, int> start, pair<char, int> end) {
		int weight = g[end.first - 'a'][8 - end.second].getWeight();
		int check = 0;
		int opponent = 0;
		vector<pair<char, int>, pair<char, int>> g = b.getGrid();

		if (b.playLegalMove(start, end)) {
	        vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves((colour == Colour::White)?Colour::Black::Colour::White);
			
			// Find the opponent move that would yield them the most points
        	for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
            	int value = weightOfMove(g, move.second);
            	if (value > opponent) opponent = value;
	        }

			return weight + check - opponent;
		} else {
			return INT_MIN;
		}
	}

public:
	pair<char, int> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);

		// For each possible move, do a simple check as to if the move immediately problematic
		// Basically just checks small things such as whether trade will be a net positive for bot
		pair<pair<pair<char, int>, pair<char, int>>, int> bestMove(make_pair(make_pair('0', 0), make_pair('0', 0)), -1);
		
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int value = valueOfMove(b, move.second);
			if (value > bestMove.second) bestMove = make_pair(move, value);
		}

		// If there is no moves that give any points, just pick the first move from possible moves (if that is empty return no valid moves)
		if (!possibleMoves.empty()) {
			if (bestMove.second != -1) {
				bestMove.first = possibleMoves[0];
			}

			// If promoting, always choose queen

			return bestMove.first;
    	} else {
    	   	// No valid moves, return a '0' instead of a letter from a to h to indicate this 
        	return {'0', 0};
		}
	}
}
