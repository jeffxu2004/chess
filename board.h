#ifndef BOARD_H
#define BOARD_H

#include "subject.h"
#include "piececreator.h"
#include "../pieces/piece.h"
#include <memory>
#include <utility>
#include <vector>
#include <string>

using namespace std;

enum Result { Win, Loss, Draw, Continue };

class Piece;

class Board : public Subject {
	vector<vector<unique_ptr<Piece>>> grid;
	Result state;
  	vector<Observer*> observers;
	Colour turn; // colour of next player's turn

public:
	Board(); // ctor

	Board(int n); //ctor with gridsize n;
	
	~Board(); // dtor

	// returns the state field
	Result getState();

	// return the turn field 
	Colour getTurn(); 

	// returns the grid
	vector<vector<unique_ptr<Piece>>> getGrid();

	// returns a pointer to the piece at the specified coordinate on the square.
	Piece* getPiece(pair<char, int> loc);
	
	//Overloads the getPiece operator to return the coordinates of piece when passing in its address
	pair<char,int> getPiece(Piece*);

	// changes the square of coords loc to piecetype p of colour side
	void changeSquare(pair<char, int> loc, PieceType p, Colour side);

	// Takes in a start coordinate which indicates which piece is being moved and moves it to the end coordinate. 
	// This function returns ture if it is valid move that does not place the king, and plays the move
	// Otherwise the function returns false and the board remains logically unchanged
	// This function may notify observers (i.e. board and king if necessary)
	bool playMove(pair<char, int> start, pair<char, int> end);

	// returns true if dest is a square that piece can functionally move to and false otherwise.
	// This function calls the getMoves() function in piece to get a vector<pair> and checks
	// whether dest is in the vector. This function does not check for checks
	bool isPlayableMove(Piece *piece, pair<char, int> dest);

	// playMove is overloarded for pawn promotion. If the pawn is promoting, the desired piece that
	// it promotes into is passed into the function as an additional parameter as well as the colour.
	void playMove(pair<char, int> start, pair<char, int> end, PieceType type, Colour side);

	// returns a list of possible moves that colour c is able to make in the current poistion
	// where the first pair is where the piece is moving from, and the second pair is where the piece is moving to
	// does not check for whether moving the piece will make its own king in check
	vector <pair <pair<char, int>, pair<char, int> >> getAllMoves(Colour c);

	// returns true if the piece is a pawn and is promoting and false otherwise.
	bool isPromoting(pair<char, int> start, pair<char, int> end);
	
    void attach(Observer* obs) override;

    void detach(Observer* obs) override;


	// notifies ALL observers
	void notifyAllObservers() override;

};

#endif
