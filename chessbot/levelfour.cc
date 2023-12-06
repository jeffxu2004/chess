#include "chessbot.h"
#include "../board.h"
#include "../pieces/piece.h"
#include <cstdlib>
#include <climits>

class LevelFour : public ChessBot {
	// Takes in a copy of the board and a pair indicating the destination of the move in question
	// Checks through all of opponents moves to see what their most valuable move is
	// Recursively checks how bot can react, then returns the difference between bot's move and opponents move
	int valueOfMove(Board &b, pair<char, int> start, pair<char, int> end, int depth, Colour colour) {
		// Get weight of own move (x10 value of move to prevent cases where bot takes losing trade just for a check)
		int weight = 2*b.getPiece(end)->getWeight();

		PieceType type = b.getPiece(start)->pieceType();
		// Check edge case where move is pawn promotion
		if (type == PieceType::Pawn && (end.second == 1 || end.second == b.getSize())) {
			type = PieceType::Queen;
		}

        // Create a copy of my piece and check if this move will result in the piece checking the king
		if (b.playMove(start, end)) {
			unique_ptr<Piece> copyPiece = PieceCreator::createPiece(type, colour, end);
			vector<pair<char, int>> moves = copyPiece->getMoves(b);
			for (auto move : moves) {
				if (b.getPiece(move)->pieceType() == PieceType::King) {
					weight += 2;
					// Prefer checking later into the game
					if (numMoves >= 20) {
						weight += 1;
					}
					break;
				}
			}

			// Base case
			if (depth == 0) return weight;

			vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(b.getTurn());
			
			// filter moves that will put king in check
			for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
				if (!b.kingIsNotCheck(move->first, move->second)) {
					possibleMoves.erase(move);
				} else {
					move++;
				}
			}

			Board copy(b.getSize());

			for (int i = 1; i <= copy.getSize(); i++) {
				for (int j = 'a'; j <= 'h'; j++) {
					pair<char, int> loc = make_pair(j, i);
					copy.changeSquare(loc, b.getPiece(loc)->pieceType(), b.getPiece(loc)->getSide());
				}
			}

			copy.setTurn(b.getTurn());

			int opponent = 0;
			// Find the opponent move that would yield them the most points
			for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
				int value = valueOfMove(copy, move->first, move->second, depth-1, b.getTurn());
				if (value > opponent) opponent = value;
			}

			return weight - opponent;
		} else {
			return INT_MIN;
		}
	}

public:
	LevelFour(Colour colour) : ChessBot{colour} {};
	
	pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);
		
		// Remove moves that put own king in check
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
			// Variable to count the number of pieces left on the board
			int numPieces = 0;

			// Make copy of board for simulating moves
			Board copy(b.getSize());

			for (int i = 1; i <= copy.getSize(); i++) {
				for (int j = 'a'; j <= 'h'; j++) {
					pair<char, int> loc = make_pair(j, i);
					copy.changeSquare(loc, b.getPiece(loc)->pieceType(), b.getPiece(loc)->getSide());
					if (b.getPiece(loc)->pieceType() != PieceType::Blank) {
						numPieces++;
					}
				}
			}

			copy.setTurn(b.getTurn());
			int moveWeight = 0;
			// Increase depth in late game situations
			if (numPieces < 14) {
				moveWeight = valueOfMove(copy, move->first, move->second, 9, this->colour);
			} else {
				moveWeight = valueOfMove(copy, move->first, move->second, 3, this->colour);
			}
			// Add one point if pawn to incentivize usage of pawn over other pieces (espeically for capturing
			if (b.getPiece(move->first)->pieceType() == PieceType::Pawn) moveWeight++;
			// Incentivize developing pieces
			if (numMoves < 6) {
				if (b.getPiece(move->first)->pieceType() == PieceType::Bishop || b.getPiece(move->first)->pieceType() == PieceType::Knight) {
					moveWeight++;
				}
			}
			
			// Bot prefers taking control of center (aids in early game so it doesn't make too many random moves)
			if (numMoves < 6) {
				if (move->second == make_pair('e', 5) || move->second == make_pair('d', 5) 
				|| move->second == make_pair('e', 4) || move->second == make_pair('d', 4)) {
					moveWeight+=2;
				}
			}

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
