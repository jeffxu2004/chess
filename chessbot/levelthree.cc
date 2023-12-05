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
        int weight = 2*b.getPiece(dest)->getWeight();

        // Create a copy of my piece and check if this move will result in the piece checking the king
		unique_ptr<Piece> copy = PieceCreator::createPiece(b.getPiece(start)->pieceType(), colour, dest);
        vector<pair<char, int>> moves = copy->getMoves(b);
        for (auto move : moves) {
            if (b.getPiece(move)->pieceType() == PieceType::King) {
                weight += 2;
                break;
            }
        }

        return weight;
    }

	// Takes in a copy of the board and a pair indicating the destination of the move in question
	// Checks through all of opponents moves to see what their most valuable move is
	// Then returns the difference between bot's move and opponents move
	int valueOfMove(Board &b, pair<char, int> start, pair<char, int> end) {
		
		// Get weight of own move (double value of move to prevent cases where bot takes losing trade just for a check)
		int weight = 2*b.getPiece(end)->getWeight();

		int opponent = 0;
		PieceType type = b.getPiece(start)->pieceType();
		
		if (b.playLegalMove(start, end)) {
			// Check edge case where move is pawn promotion
			if ((this->colour == Colour::Black && type == PieceType::Pawn && end.second == 1)
			|| (this->colour == Colour::White && type == PieceType::Pawn && end.second == 8)) {
				type = PieceType::Queen;
			}
			// Get points for own move first
			vector<pair<char, int>> moves = b.getPiece(end)->getMoves(b);
			for (auto move : moves) {
				if (b.getPiece(move)->pieceType() == PieceType::King) {
					weight += 2;
				}
				// Bot prefers taking control of center (aids in early game so it doesn't make too many random moves)
				if (numMoves < 8) {
					if (((move == make_pair('e', 5) || move == make_pair('d', 5)) && this->colour == Colour::White)
					|| ((move == make_pair('e', 4) || move == make_pair('d', 4)) && this->colour == Colour::Black)) {
						weight++;
					}
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
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            if (!b.kingIsNotCheck(move->first, move->second)) {
                possibleMoves.erase(move);
            } else {
                move++;
            }
        }

		// Basically just decides whether to avoid or capture based on
		// whether trade will be a net positive for bot
		int bestWeight = INT_MIN;
		vector<pair<pair<char, int>, pair<char, int>>> bestMoves;
		
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			// Make copy of board for simulating moves
			Board copy(b.getSize());

			for (int i = 1; i <= copy.getSize(); i++) {
				for (int j = 'a'; j <= 'h'; j++) {
					pair<char, int> loc = make_pair(j, i);
					copy.changeSquare(loc, b.getPiece(loc)->pieceType(), b.getPiece(loc)->getSide());
				}
			}

			copy.setTurn(b.getTurn());

			int moveWeight = valueOfMove(copy, move->first, move->second);
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
		if (bestWeight != INT_MIN) {
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
