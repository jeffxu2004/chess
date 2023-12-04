#include "chessbot.h"
#include "../board.h"
#include "../pieces/piece.h"
#include <cstdlib>
#include <climits>

class LevelThree : public ChessBot {
    // Takes in the grid and a pair indicating the destination of the move in question
    // This function returns zero if the destination is an empty square, otherwise it returns
    // the weight of the piece taken.
    // Checks have a weight of two. (If a move takes a piece and checks the enemy king, the weight is summed)
    int weightOfMove(Board &b, pair<char, int> start, pair<char, int> dest, Colour colour) {
        int weight = b.getPiece(dest)->getWeight();

        // Create a copy of my piece and check if this move will result in the piece checking the king
		unique_ptr<Piece> copy = PieceCreator::createPiece(b.getPiece(start)->pieceType(), colour, dest);
        vector<pair<char, int>> moves = copy->getMoves(b);
        for (auto move : moves) {
            if (b.getPiece(move)->pieceType() == PieceType::King) {
                weight += 2;
                break;
            }
			pair<char, int> coords = b.getPiece(move)->getCoords();
			if (coords == make_pair('d', 4) || coords == make_pair('d', 5) ||
				coords == make_pair('e', 4) || coords == make_pair('e', 5)) {
				weight++;
			}
        }

        return weight;
    }

	// Takes in a copy of the board and a pair indicating the destination of the move in question
	// Checks through all of opponents moves to see what their most valuable move is
	// Then returns the difference between bot's move and opponents move
	int valueOfMove(Board& b, pair<char, int> start, pair<char, int> end) {
		// Get weight of own move
		int weight = b.getPiece(end)->getWeight();

		int opponent = 0;
		if (b.playLegalMove(start, end)) {
			// Get points for own move first
			vector<pair<char, int>> moves = b.getPiece(end)->getMoves(b);
			for (auto move : moves) {
				if (b.getPiece(move)->pieceType() == PieceType::King) {
					weight += 2;
					break;
				}
				// Bot prefers taking control of center (aids in early game so it doesn't make too many random moves)
				pair<char, int> coords = b.getPiece(move)->getCoords();
				if (coords == make_pair('d', 4) || coords == make_pair('d', 5) ||
					coords == make_pair('e', 4) || coords == make_pair('e', 5)) {
					weight++;
				}
			}

			Colour side = (colour == Colour::White)?Colour::Black:Colour::White;
	        vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(side);
			
			// filter moves that will put king in check
        	for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            	if (!b.kingIsNotCheck(move->first, move->second)) {
                	possibleMoves.erase(move);
            	} else {
                	move++;
            	}
        	}

			// Find the opponent move that would yield them the most points
        	for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
            	int value = weightOfMove(b, move->first, move->second, side);
            	if (value > opponent) opponent = value;
	        }

			return weight - opponent;
		} else {
			return INT_MIN;
		}
	}

public:
	LevelThree(Colour colour) : ChessBot{colour} {};
	
	pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);

		// For each possible move, do a simple check as to if the move immediately problematic
		// Basically just checks small things such as whether trade will be a net positive for bot
		pair<pair<pair<char, int>, pair<char, int>>, int> bestMove(make_pair(make_pair('0', 0), make_pair('0', 0)), INT_MIN);
		
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int value = valueOfMove(b, move->first, move->second);
			if (value > bestMove.second) bestMove = make_pair(*move, value);
		}

		// If there is no moves that give any points, just pick the first move from possible moves (if that is empty return no valid moves)
		if (bestMove.second != INT_MIN) {
			// If promoting, always choose queen
            if (b.isPromoting(bestMove.first.first, bestMove.first.second)) {
                b.setPromotionPiece(PieceType::Queen);
            }

			return bestMove.first;
    	} else {
    	   	// No valid moves, return a '0' instead of a letter from a to h to indicate this 
        	return bestMove.first;
		}
	}
};
