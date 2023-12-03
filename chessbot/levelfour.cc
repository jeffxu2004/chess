#include "chessbot.h"
#include "../board.h"
#include "../pieces/piece.h"
#include <cstdlib>
#include <climits>

class LevelFour : public ChessBot {
    // Gives a weight to the move
    int weightOfMove(Board &b, pair<char, int> start, pair<char, int> dest) {
        int weight = b.getPiece(dest)->getWeight();

        // Create a copy of my piece and check if this move will result in the piece checking the king
        Piece* copy = b.getPiece(start);
        copy->setCoords(dest);
        vector<pair<char, int>> moves = copy->getMoves(b);
        for (auto move : moves) {
            if (b.getPiece(move)->pieceType() == PieceType::King) {
                weight += 2;
            }
			pair<char, int> coords = b.getPiece(move)->getCoords();
			if (coords == make_pair('d', 4) || coords == make_pair('d', 5) ||
				coords == make_pair('e', 4) || coords == make_pair('e', 5)) {
				weight++;
			}
        }

        return weight;
    }

	// Recursively reads depth moves ahead and returns an integer indicating the value of the move
	// pieces are worth weight, checks have a value of two, and pieces that threaten middle squares and squares near king are worth 1
	int valueOfMove(Board& b, pair<char, int> start, pair<char, int> end, int depth, Colour col) {
		if (depth == 0) {
			return 0;
		}

		int weight = b.getPiece(end)->getWeight();
		int check = 0;
		int opponent = 0;

		col = (col == Colour::White)?Colour::Black:Colour::White;
		b.playLegalMove(start, end);
        vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(col);

		// getAllMoves does not consider if the move will place/leave the king in check,
		// as a result we must filter out those moves		
        for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            if (b.kingIsNotCheck(move->first, move->second)) {
                possibleMoves.erase(move);
            } else {
                move++;
            }
        }
		
		// Find the opponent move that would yield them the most points
		int best = INT_MIN;
      	for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
        	int value = weightOfMove(b, move->first, move->second);
			int recurse = value + valueOfMove(b, move->first, move->second, depth-1, col);
			if (recurse > best) {
				best = recurse;
			}
		}

		return best;
	}

public:
	LevelFour(Colour colour) : ChessBot{colour} {};

	pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) override {
		vector<pair<pair<char, int>, pair<char, int>>> possibleMoves = b.getAllMoves(this->colour);

		// getAllMoves does not consider if the move will place/leave the king in check,
		// as a result we must filter out those moves		
        for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ) {
            if (b.kingIsNotCheck(move->first, move->second)) {
                possibleMoves.erase(move);
            } else {
                move++;
            }
        }

		// For each possible move, check up to a few moves ahead and choose which move has the most value
		pair<pair<pair<char, int>, pair<char, int>>, int> bestMove(make_pair(make_pair('0', 0), make_pair('0', 0)), INT_MIN);
		
		for (auto move = possibleMoves.begin(); move != possibleMoves.end(); ++move) {
			int value = valueOfMove(b, move->first, move->second, 2, this->colour);
			if (value > bestMove.second) bestMove = make_pair(*move, value);
		}

		// If there is no moves that give any points, just pick the first move from possible moves (if that is empty return no valid moves)
		if (!possibleMoves.empty()) {
			bestMove.first = possibleMoves[0];

			// If promoting, always choose queen
            if (b.isPromoting(bestMove.first.first, bestMove.first.second)) {
                b.setPromotionPiece(PieceType::Queen);
            }
			
			b.playLegalMove(bestMove.first.first, bestMove.first.second);

			return bestMove.first;
    	} else {
			// No valid moves
        	return bestMove.first;
		}
	}
};