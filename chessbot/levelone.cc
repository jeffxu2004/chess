#include "chessbot.h"
#include "../board.h"
#include "../pieces/piece.h"
#include <cstdlib>

class LevelOne : public ChessBot {
public:
	LevelOne(Colour colour) : ChessBot{colour} {};
	
	pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);
	
		// getAllMoves does not consider if the move will place/leave the king in check,
		// as a result we must filter out those moves		
        for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            if (!b.kingIsNotCheck(move->first, move->second)) {
                possibleMoves.erase(move);
            } else {
                move++;
            }
        }
		
		if (!possibleMoves.empty()) {
    	    // Level one bot makes random moves so we use srand and rand
    		// Seed the random number generator
    		srand(static_cast<unsigned int>(time(nullptr)));

 	    	// Mod the number by the length of the array of moves
			// so that the number represents a random index in the list of moves
    		int index = rand()%possibleMoves.size();
			
			// If pawn is promoting, pick random piece
			if (b.isPromoting(possibleMoves[index].first, possibleMoves[index].second)) {
				int r = rand()%4;
				if (r == 0) b.setPromotionPiece(PieceType::Queen);
				else if (r == 1) b.setPromotionPiece(PieceType::Rook);
				else if (r == 2) b.setPromotionPiece(PieceType::Knight);
				else if (r == 3) b.setPromotionPiece(PieceType::Bishop);
			}

			return possibleMoves[index];
    	} else {
    	   	// No valid moves, return a '0' instead of a letter from a to h to indicate this 
        	return {{'0', 0}, {'0', 0}};
		}
	}
};
