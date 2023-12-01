#include "chessbot.h"
#include "../board.h"
#include "../pieces/piece.h"
#include <cstdlib>
#include <limits>

class LevelFour : ChessBot {
    // Takes in the grid and a pair indicating the destination of the move in question
    // This function returns zero if the destination is an empty square, otherwise it returns
    // the weight of the piece taken.
    // Checks have a weight of two. (If a move takes a piece and checks the enemy king, the weight is summed)
    int weightOfMove(Board &b, pair<char, int> start, pair<char, int> dest) {
        int weight = b.getPiece(dest)->getWeight();
        int check = 0;

        // Create a copy of my piece and check if this move will result in the piece checking the king
        Piece copy = *b.getPiece(start);
        copy.setCoords(dest);
        vector<pair<char, int>> moves = copy.getMoves();
        for (auto move : moves) {
            if (b.getPiece(move)->PieceType == PieceType::King) {
                check = 2;
                break;
            }
        }

        return weight + check;
    }

	// Recursively reads depth moves ahead and returns an integer indicating the value of the move
	// pieces are worth weight, checks have a value of two, and pieces that threaten middle squares and squares near king are worth 1
	int valueOfMove(Board b, pair<char, int> start, pair<char, int> end, int depth, Colour col) {
		if (depth == 0) {
			return 0;
		}

		int weight = b.getPiece(end)->getWeight();
		int check = 0;
		int opponent = 0;

		col = (col == Colour::White)?Colour::Black::Colour::White;
		if (b.playLegalMove(start, end)) {
	        vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(col);
			
			// Find the opponent move that would yield them the most points
        	for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
            	int value = weightOfMove(b, move.first, move.second);
				int recurse = valueOfBoard(b, );
            	if (col == this->colour) {
					value = value - 
				} else {
					value = 
				}
	        }

			} else {
				return weight + check - opponent + valueOfMove(b, );
			}
		} else {
			return INT_MIN;
		}
	}

public:
	pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);

		// For each possible move, check up to a few moves ahead and choose which move has the most value
		pair<pair<pair<char, int>, pair<char, int>>, int> bestMove(make_pair(make_pair('0', 0), make_pair('0', 0)), -1);
		
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int value = valueOfMove(b, move.first, move.second, 2);
			if (value > bestMove.second) bestMove = make_pair(move, value);
		}

		// If there is no moves that give any points, just pick the first move from possible moves (if that is empty return no valid moves)
		if (!possibleMoves.empty()) {
			if (bestMove.second != -1) {
				bestMove.first = possibleMoves[0];
			}

			// If promoting, always choose queen
            if (b.isPromoting(bestMove.first.first, bestMove.first.second)) {
                b.setPromotingPiece(PieceType::Queen);
            }
			
			playLegalMove(bestMove.first.first, bestMove.first.second);

			return bestMove.first;
    	} else {
    	   	// No valid moves, return a '0' instead of a letter from a to h to indicate this 
        	return {'0', 0};
		}
	}
}
