#ifndef BOARD_H
#define BOARD_H

#include "pieces/piece.h"
#include "piececreator.h"
#include "enumClasses.h"
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Piece;
class Board {
	vector<vector<unique_ptr<Piece>>> grid;
	Result state = ::Result::Continue;
  	vector<Observer*> observers;
	Colour turn = Colour::White; // colour of next player's turn
	PieceType promotionPiece = PieceType::Queen;
	int size;

public:
	Board(int n); //ctor with gridsize n;
	
	~Board(); // dtor

	// returns the state field
	Result getState() const;

	// return the turn field 
	Colour getTurn() const; 

	// returns promotion piece
	PieceType getPromotionPiece() const;

	// returns the grid
	vector<vector<Piece *>> getGrid() const;

	// returns a pointer to the piece at the specified coordinate on the square.
	Piece* getPiece(pair<char, int> loc);

	// return a pointer of piece King of colour c
	Piece* getKing(Colour c);
	
	//Overloads the getPiece operator to return the coordinates of piece when passing in its address
	pair<char,int> getPiece(Piece*);

	//Get size of board
	int getSize();

	//set promotion piece
	void setPromotionPiece(PieceType p);

	//set result
	void setResult(Result r);

	//sets trun
	void setTurn(Colour c);

	// Initalizes the conventional chessboard with its respective pieces
	void standardInit();

	// Makes board filled with blank squares
	void clearBoard();

	// Prints true if the custom setup is valid
	bool validSetup();

	// returns true if its only king v king
	bool checkDraw();

	// changes the square of coords loc to piecetype p of colour side
	void changeSquare(pair<char, int> loc, PieceType p, Colour side);

	void changeSquare(char c, pair<char,int> location);

	// Takes in a start coordinate which indicates which piece is being moved and moves it to the end coordinate. 
	// This function returns ture if it is valid move that does not place the king, and plays the move
	// Otherwise the function returns false and the board remains logically unchanged
	// This function may notify observers (i.e. board and king if necessary)
	bool playMove(pair<char, int> start, pair<char, int> end);

	// returns true if dest is a square that piece can functionally move to and false otherwise.
	// This function calls the getMoves() function in piece to get a vector<pair> and checks
	// whether dest is in the vector. This function does not check for checks
	bool isPlayableMove(Piece *piece, pair<char, int> dest);

	// returns a list of possible moves that colour c is able to make in the current poistion
	// where the first pair is where the piece is moving from, and the second pair is where the piece is moving to
	// does not check for whether moving the piece will make its own king in check
	vector <pair <pair<char, int>, pair<char, int> >> getAllMoves(Colour c);

	// returns true if the own king is not in check(legal move) after playing the move 
	// i.e. calls checKmove(start, end, true);
	bool kingIsNotCheck(pair<char, int> start, pair<char, int> end);

	// plays move and notifies king observers if kingIsNotCheck is true
	// otherwise return false and does nothing
	bool playLegalMove(pair<char, int> start, pair<char, int> end);

	// returns true if the move is legal, i.e. doesn't put the king in check
	// plays the move if revert is false, otherwise doesnt change the board
	bool checkLegalMove(pair<char, int> start, pair<char, int> end, bool revert);

	// returns true if the piece is a pawn and is promoting and false otherwise.
	bool isPromoting(pair<char, int> start, pair<char, int> end);

	// returns true if the piece is a king and is castling
	bool isCastle(pair<char, int> start, pair<char, int> end);

	// returns true if the current move is enpassent 
	bool isEnPas(pair<char, int> start, pair<char, int> end);
	
    void attach(Observer* obs);

    void detach(Observer* obs);

	// notifies ALL observers
	void notifyAllObservers(const Piece* p, Colour turn) const;

};

#endif
