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

		PieceType type = b.getPiece(start)->pieceType();
		// Check edge case where move is pawn promotion
		if ((this->colour == Colour::Black && type == PieceType::Pawn && dest.second == 1)
		|| (this->colour == Colour::White && type == PieceType::Pawn && dest.second == 8)) {
			type = PieceType::Queen;
		}
		// Create a copy of my piece and check if this move will result in the piece checking the king
		unique_ptr<Piece> copy = PieceCreator::createPiece(type, this->colour, dest);
		vector<pair<char, int>> moves = copy->getMoves(b);
		for (auto move : moves) {
			if (b.getPiece(move)->pieceType() == PieceType::King) {
				check = 2;
				break;
			}
			// Bot prefers taking control of center (aids in early game so it doesn't make too many random moves)
			if (numMoves < 4) {
				if (move == make_pair('e', 5) || move == make_pair('d', 5) || move == make_pair('e', 4) || move == make_pair('d', 4)) {
					weight++;
				}
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

		// Have a vector of pairs to keep track of the most valuable moves
		// Most valuable move calculated by what gives most points
		int bestWeight = -1;
		vector<pair<pair<char, int>, pair<char, int>>> bestMoves;
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int moveWeight = weightOfMove(b, move->first, move->second);
			// Add one point if pawn to incentivize usage of pawn over other pieces (espeically for capturing
			if (b.getPiece(move->first)->pieceType() == PieceType::Pawn) moveWeight++;

			// If move is equal to previously found best move, add as potential move
			if (moveWeight == bestWeight) {
				bestMoves.push_back(*move); 
			// If found a new best move, clear previous array of potential best moves
			} else if (moveWeight > bestWeight) {
				bestWeight = moveWeight;
				bestMoves.clear();
				bestMoves.push_back(*move);
			}
		}
		numMoves++;

		// If there is no moves that give any points, just pick the first move from possible moves (if that is empty return no valid moves)	
		if (bestWeight != -1) {
			// Have some randomness in moves so bot isn't so predictable
			// Also prevents situations were bot vs bot results in infinite loop
    		srand(static_cast<unsigned int>(time(nullptr)));
			int index = rand()%bestMoves.size();

			if (b.isPromoting(bestMoves[index].first, bestMoves[index].second)) {
				b.setPromotionPiece(PieceType::Queen);
			}

			return bestMoves[index];
    	} else {
    	   	// No valid moves, return a '0' instead of a letter from a to h to indicate this 
        	return make_pair(make_pair('0', 0), make_pair('0', 0));
		}
	}
};
