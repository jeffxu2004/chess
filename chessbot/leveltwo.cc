#include "chessbot.h"
#include <cstdlib>

class LevelTwo : ChessBot {
	// Takes in the grid and a pair indicating the destination of the move in question
	// This function returns zero if the destination is an empty square, otherwise it returns
	// the weight of the piece taken.
	// Checks have a weight of two. (If a move takes a piece and checks the enemy king, the weight is summed)
	int weightOfMove(vector<vector<unique_ptr<Piece>>> &g, pair<char, int> dest) {
		int weight = g[dest.first - 'a'][8 - dest.second].getWeight();
		int check = 0;
		return weight + check;
	}
public:
	pair<char, int> getNextMove(Board &b) override {
		// Keep a copy of grid for filtering moves
		vector<vector<unique_ptr<Piece>>> cpuGrid = b.getGrid(); 
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);

		// getAllMoves does not consider if the move will place/leave the king in check,
		// as a result we must filter out those moves
        for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            if (b.kingIsNotCheck(move.first, move.second) {
                possibleMoves.erase(move);
            } else {
                move++;
            }
        }

		// Have a pair to keep track of the most valuable move and its value
		// Most valuable move calculated by what gives most points
		pair<pair<pair<char, int>, pair<char, int>>, int> bestMove(make_pair(make_pair('0', 0), make_pair('0', 0)), -1);
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int moveWeight = weightOfMove(cpuGrid, move.second);
			if (moveWeight > bestMove.second) bestMove = make_pair(move, moveWeight);
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
