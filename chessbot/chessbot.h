#ifndef CHESS_BOT_H
#define CHESS_BOT_H

#include <vector>
#include <utility>

using namespace std;

class Piece;
class Board;

class ChessBot {
protected:
	Colour colour;
public:
    ChessBot();
	// Returns the next move that the bot makes
    virtual pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) = 0;
	virtual ~ChessBot() = default;
};

#endif
