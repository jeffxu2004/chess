#include <vector>
#include <utility>
#include "piece.h"
#include "../observer.h"

using namespace std;

class Board;

class King: public Piece, public Observer {
	// tracks the subjects that the king is observing to make it easier to determine the
	// legality of a move when the king is in check
	bool check;
	bool moved;
	bool hasCastled;

	vector<Piece*> subjects;
	
public:
	King(int weight, Colour side, pair<char,int> coords); // ctor
	~King() override = default; // dtor
	
	// Overrides from Piece:	
	vector<pair<char, int>> getMoves(const Board &b) const override;

	PieceType pieceType() const override;


	// Overrides from Observer:
	Subscription getSubscription() const;
	
	void notify(const Subject* item, const Board* b) override;


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
	bool hasMoved() const;
	bool justCastled() const;
};
