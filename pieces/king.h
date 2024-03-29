#ifndef KING_H
#define KING_H
#include <vector>
#include <utility>
#include "piece.h"
#include "../observer.h"
#include "rook.h"

using namespace std;

class Board;

class King: public Piece, public Observer {
	// tracks the subjects that the king is observing to make it easier to determine the
	// legality of a move when the king is in check
	bool check;
	bool moved = true;
	bool hasCastled;

	vector<Piece*> subjects;
	
public:
	King(int weight, Colour side, pair<char,int> coords); // ctor
	~King() override = default; // dtor
	
	// Overrides from Piece:	
	vector<pair<char, int>> getMoves(const Board& b) const override;

	PieceType pieceType() const override;


	// Overrides from Observer:
	Subscription getSubscription() const;
	
	void notify(const Piece* item, const Board* b) override;
	void notify(const Piece* item, Colour turn) override {};

	// Accessors and Mutators
	// returns a vector of the subjects that the king is observing	
	vector<Piece*> getSubjects() const;

	// sets a vector as the subject
	void setSubjects(vector<Piece*> newSubjects);

	// clears the subjects vector in king
	void clearSubjects();
	
	// appends a subject to the end of the vector
	void addSubject(Piece* subject);

	// removes subject from subjects
	void dropSubject(Piece* subject);

	bool inCheck() const;
	void setCheck(bool check);
	bool hasMoved() const;
	void setMoved(bool moved);
	bool justCastled() const;
	void setCastled(bool castled);
};

#endif
