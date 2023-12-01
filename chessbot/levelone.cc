#include "chessbot.h"
#include <cstdlib>

class LevelOne : ChessBot {
public:
	pair<char, int> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);
	
		// getAllMoves does not consider if the move will place/leave the king in check,
		// as a result we must filter out those moves		
        for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            if (kingIsNotCheck(move.first, move.second) {
                possibleMoves.erase(move);
            } else {
                move++;
            }
        }
		
		if (!possibleMoves.empty()) {
    	    // Level one bot makes random moves so we use srand and rand
    		// Seed the random number generator
    		srand(static_cast<unsigned int>(std::time(nullptr)));

 	    	// Mod the number by the length of the array of moves
			// so that the number represents a random index in the list of moves
    		int index = rand()%possibleMoves.size();
			bool play = playLegalMove(possibleMoves[index]);

			// If pawn is promoting, pick random piece
			if (b.isPromoting(possibleMoves[index].first, possibleMoves[index].second)) {
				// Nothing yet
			}

			return possibleMoves[index];
    	} else {
    	   	// No valid moves, return a '0' instead of a letter from a to h to indicate this 
        	return {'0', 0};
		}
	}
}
