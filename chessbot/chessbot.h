#ifndef CHESS_BOT_H
#define CHESS_BOT_H

#include <vector>
#include <utility>
#include "../enumClasses.h"

using namespace std;

class Piece;
class Board;

class ChessBot {
protected:
	Colour colour;
	// stores the last three moves played by the bot to avoid repetition
	vector<pair<pair<char,int>, pair<char,int>>> lastThreeMoves; 
public:
	ChessBot(Colour colour) : colour{colour} {};
	// Returns the next move that the bot makes
    virtual pair<pair<char, int>, pair<char, int>> getNextMove(Board &b) = 0;
	virtual ~ChessBot() = default;
};

#endif
