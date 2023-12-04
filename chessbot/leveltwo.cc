#include "chessbot.h"
#include "../board.h"
#include "../pieces/piece.h"
#include "../piececreator.h"
#include <cstdlib>

class LevelTwo : public ChessBot {
	// Takes in the grid and a pair indicating the destination of the move in question
	// This function returns zero if the destination is an empty square, otherwise it returns
	// the weight of the piece taken.
	// Checks have a weight of two. (If a move takes a piece and checks the enemy king, the weight is summed)
	int weightOfMove(Board &b, pair<char, int> start, pair<char, int> dest) {
		// This bot wants to capture pieces so lets scale the value of pieces by a factor of two
		int weight = 2*b.getPiece(dest)->getWeight();
		int check = 0;

		// Create a copy of my piece and check if this move will result in the piece checking the king
		unique_ptr<Piece> copy = PieceCreator::createPiece(b.getPiece(start)->pieceType(), this->colour, dest);
		vector<pair<char, int>> moves = copy->getMoves(b);
		for (auto move : moves) {
			if (b.getPiece(move)->pieceType() == PieceType::King) {
				check = 2;
				break;
			}
			// Bot prefers taking control of center (aids in early game so it doesn't make too many random moves)
			pair<char, int> coords = b.getPiece(move)->getCoords();
			if (coords == make_pair('d', 4) || coords == make_pair('d', 5) ||
				coords == make_pair('e', 4) || coords == make_pair('e', 5)) {
				weight++;
			}
		}
	
		return weight + check;
	}
public:
	LevelTwo(Colour colour) : ChessBot{colour} {};
	
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

		// Have a pair to keep track of the most valuable move and its value
		// Most valuable move calculated by what gives most points
		pair<pair<pair<char, int>, pair<char, int>>, int> bestMove(make_pair(make_pair('0', 0), make_pair('0', 0)), -1);
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int moveWeight = weightOfMove(b, move->first, move->second);
			if (moveWeight > bestMove.second) bestMove = make_pair(*move, moveWeight);
		}

		// If there is no moves that give any points, just pick the first move from possible moves (if that is empty return no valid moves)	
		if (bestMove.second != -1) {
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
